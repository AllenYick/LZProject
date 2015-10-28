#include "lz_mainwindow.h"
#include "LZCamera.h"
#include <fstream>

LZ_MainWindow::LZ_MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	// 初始化显示图片
	ui.hardwareEdit->setPixmap(QPixmap(":/resource/cross.png"));       // 显示图片
	ui.cameraStatusLabel->setPixmap(QPixmap(":/resource/collectstatus1_2.png"));
	ui.inOutHoleLabel->setPixmap(QPixmap(":/resource/lightouthole.png"));
	// 初始化变量
	bIsPressInholeButton_ = false;
	bIsPressOutholeButton_ = false;
	bIsInitCamera_ = false;
	bIsInitHardware_ = false;
	workMode_ = WKM_MANUAL;           // 默认手动模式
	bIsReadFromMPC_ = false;
	bIsInHole_ = false;
	bIsPreInHole_ = false;           // 默认出洞
	vBitsReadFromMPC_.resize(NUM_BITS, false);
	vBitsWriteToA_FromMPC_.resize(NUM_BITS, false);
	vBitsWriteToA_IOH_.resize(NUM_BITS, false);
	vBitsWriteToMPC_IOH_.resize(NUM_BITS, false);
	
	// 初始化自动检测进程
	pAutoDetectThread_ = new AutoDetectThread();
	
	// 初始化读写硬件指针
	pReadHardWareThread_ = new ReadHardwareThread(PORT_NUM_READ_FROM_MPC, NUM_BITS);
	pWriteToMPC_IOH_ = new WriteHardware(PORT_NUM_WRITE_TO_MPC, NUM_BITS);
	pWriteToA_IOH_ = new WriteHardware(PORT_NUM_WRITE_IOH_TO_A, NUM_BITS);    
	pWriteToA_FromMPC_ = new WriteHardware(PORT_NUM_WRITE_TO_A, NUM_BITS);

	/* 设置进出洞快捷方式，'+'进洞，'Enter'出洞 */
	ui.setInHoleButton->setShortcut(Qt::Key_Plus);
	ui.setOutHoleButton->setShortcut(Qt::Key_Enter);
	// 设置信号与槽
	// for button
	connect(ui.setInHoleButton, SIGNAL(clicked()), this, SLOT(onSetInHoleButton()));
	connect(ui.setOutHoleButton, SIGNAL(clicked()), this, SLOT(onSetOutHoleButton()));
	connect(ui.initCameraButton, SIGNAL(clicked()), this, SLOT(initCameras()));
	//for action
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(onActionAbout()));  
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(onActionExit()));
	// for signal
	// @brief  自动检测进程发回的进出洞信号 
	connect(pAutoDetectThread_, SIGNAL(sendStatus(bool,bool,int, double, double)), this, 
		SLOT(receiveStatus(bool,bool,int, double, double)));
	// @brief  自动检测进程发回的异常信号 
	connect(pAutoDetectThread_, SIGNAL(sendException(const char *)), this, SLOT(receiveException(const char *)), Qt::DirectConnection);
	// @brief  自动检测进程发回显示图像的消息 
	connect(pAutoDetectThread_, SIGNAL(sendImg(const QImage &,bool)), this, SLOT(receiveImg(const QImage &,bool)));
	// @brief  改变工作模式发回的消息 
	connect(pReadHardWareThread_, SIGNAL(sendModeChange(bool, bool, bool, bool)), this, SLOT(receiveModeChange(bool, bool, bool, bool)), Qt::DirectConnection);

	ui.setOutHoleButton->setEnabled(false);
	// 初始化硬件 readHardwareThread,writeToM_PC,writeToA， 并接受M_PC发来的信号
	initHardware(); 
	initCameras();
	pReadHardWareThread_->start();
}

/* @brief initialize hardware  */
void LZ_MainWindow::initHardware()
{
	try
	{
		pWriteToMPC_IOH_->init();
		pWriteToA_IOH_->init();
		pWriteToA_FromMPC_->init();
		pReadHardWareThread_->init();
	}
	catch(std::exception &e)
	{
		QMessageBox::warning(this,tr("错误"),tr("未打开硬件！"),QMessageBox::Yes);
		return;
	}
	bIsInitHardware_ = true;
	ui.hardwareEdit->setPixmap(QPixmap(":/resource/ok.png"));       // 显示图片            
}

/*
  改变工作模式
*/
void LZ_MainWindow::receiveModeChange(bool b0, bool b1, bool b2, bool b3)
{
	vBitsReadFromMPC_[0] = b0;
	vBitsReadFromMPC_[1] = b1;
	vBitsReadFromMPC_[2] = b2;
	vBitsReadFromMPC_[3] = b3;

	if((vBitsReadFromMPC_[0] == 1) && (vBitsReadFromMPC_[1]==0))      // 10:自由触发
		workMode_ = WKM_TESTING;
	else if((vBitsReadFromMPC_[0] == 0) && (vBitsReadFromMPC_[1]==1)) // 01:自动
		workMode_ = WKM_AUTO;
	else                                                              // 00:手动
		workMode_ = WKM_MANUAL;
	QString display =QTime::currentTime().toString("[hh:mm:ss]")+"\t读取到来自M_PC的消息,";
	display += "\t工作模式为:"+ strategyToStr() + "\n";
	display += QString("\t状态为:%1 %2\n").arg(vBitsReadFromMPC_[2]).arg(vBitsReadFromMPC_[3]);
	ui.informationEdit->insertPlainText(display);
	ui.modeEdit->setText(strategyToStr());
	ui.informationEdit->moveCursor(QTextCursor::End);
	if (workMode_ == WKM_AUTO)
	{
		ui.imagesShowBox->setVisible(true);
		this->setGeometry(QRect(200, 200, 982, 677));
	}
	else
	{
		ui.imagesShowBox->setVisible(false);
		this->setGeometry(QRect(200, 200, 982-420, 677));
	}
	/*
	 P1口:写到A
		| D5:自由触发模式位，1：有效
		| D6:进出洞位       1：有效
	*/
	vBitsWriteToA_IOH_[5] = (workMode_==WKM_TESTING); // 自由触发位   
	vBitsWriteToA_IOH_[6] = 0;                      // 进出洞位，默认出洞

	/*
	P5口:写到M_PC 
	   |  D0D1 为进出洞状态,默认出洞
	      00(0)：出洞  10(2)：预进洞  11(3)：进洞
	*/ 
	vBitsWriteToMPC_IOH_[0] = 0;        // S0
	vBitsWriteToMPC_IOH_[1] = 0;        // S1     
	pWriteToMPC_IOH_->write(vBitsWriteToMPC_IOH_);
	/*
	 P2口:写到A，转发来自M_PC的消息
	    | D7D6:自由触发模式
	       00:30Hz 01:50Hz  10:40Hz 11: 60Hz
	    | D5: 自动检测位  0:有效  1:无效
	*/
	vBitsWriteToA_FromMPC_[7] = vBitsReadFromMPC_[2];
	vBitsWriteToA_FromMPC_[6] = vBitsReadFromMPC_[3];
	vBitsWriteToA_FromMPC_[5] = !(workMode_ == WKM_AUTO);  // 自动检测位，低位有效
	ui.modeEdit->setText(strategyToStr());
	pWriteToA_FromMPC_->write(vBitsWriteToA_FromMPC_);
	pWriteToA_IOH_->write(vBitsWriteToA_IOH_);

	if(workMode_ == WKM_AUTO )
	{
		ui.setInHoleButton->setEnabled(false);
		ui.setOutHoleButton->setEnabled(false);
		if(bIsInitCamera_ == false)
		{
			ui.informationEdit->insertPlainText(QTime::currentTime().toString("[hh:mm:ss]") + "\t相机未初始化，不能工作在自动模式\n");
			return;
		}
		pAutoDetectThread_->start();
	}
	else if(pAutoDetectThread_->isRunning())
	{
		pAutoDetectThread_->stop();
		ui.setInHoleButton->setEnabled(true);
		ui.setOutHoleButton->setEnabled(false);
	}
	else
	{
		ui.setInHoleButton->setEnabled(true);
		ui.setOutHoleButton->setEnabled(false);
	}
}
/* 
 初始化相机
*/
void LZ_MainWindow::initCameras()
{
	if(bIsInitCamera_ == true)
		return;
	ui.informationEdit->insertPlainText(QTime::currentTime().toString("[hh:mm:ss]")+"\t正在初始化相机...\n");
		
	try
	{
		pAutoDetectThread_->init();
	}
	catch (LzException& e)
	{
		qDebug() << e.what();
		ui.informationEdit->insertPlainText(QTime::currentTime().toString("[hh:mm:ss]")+QString("\t初始化相机失败\n"));
		QMessageBox::warning(this,tr("警告"),tr("未打开相机！"),QMessageBox::Yes);
		return;
	}
	ui.informationEdit->insertPlainText(QTime::currentTime().toString("[hh:mm:ss]")+"\t初始化相机成功\n");
	ui.cameraStatusLabel->setPixmap(QPixmap(":/resource/collectstatus1.png"));
	bIsInitCamera_ = true;
}

/**
 *  @brief 手动模式进洞
*/
void LZ_MainWindow::onSetInHoleButton()
{
	if(bIsPressInholeButton_ ){
		return;
	}
	ui.setInHoleButton->setEnabled(false);
	ui.setOutHoleButton->setEnabled(true);
	ui.inOutHoleLabel->setPixmap(QPixmap(":/resource/lightinhole.png"));
	if(bIsInitHardware_ == false)
	{
		return;
	}
	vBitsWriteToA_IOH_[6] = 1;
	vBitsWriteToMPC_IOH_[0] = 1;
	vBitsWriteToMPC_IOH_[1] = 1;
	try
	{
		pWriteToA_IOH_->write(vBitsWriteToA_IOH_);
		pWriteToMPC_IOH_->write(vBitsWriteToMPC_IOH_);
	}
	catch(std::exception)
	{
		QMessageBox::warning(this,tr("警告"),tr("写入硬件错误，请检查USB模块！"),QMessageBox::Yes);
		ui.informationEdit->insertPlainText( QTime::currentTime().toString("[hh:mm:ss]")+"\tWrite Hardware failed!\n");
		ui.informationEdit->moveCursor(QTextCursor::End);
		return;
	}
	ui.informationEdit->insertPlainText(QTime::currentTime().toString("[hh:mm:ss]") + "\t进洞\t--\n");
	ui.informationEdit->moveCursor(QTextCursor::End);
	bIsPressInholeButton_ = true;
	bIsPressOutholeButton_ = false;
}

/**
 *  @brief 手动模式出洞
*/
void LZ_MainWindow::onSetOutHoleButton()
{
	if(bIsPressOutholeButton_)
		return;
	ui.setInHoleButton->setEnabled(true);
	ui.setOutHoleButton->setEnabled(false);
	ui.inOutHoleLabel->setPixmap(QPixmap(":/resource/lightouthole.png"));
	if(!bIsInitHardware_)
		return;
	vBitsWriteToA_IOH_[6] = 0;
	vBitsWriteToMPC_IOH_[0] = 0;
	vBitsWriteToMPC_IOH_[1] = 0;
	try
	{
		pWriteToA_IOH_->write(vBitsWriteToA_IOH_);
		pWriteToMPC_IOH_->write(vBitsWriteToMPC_IOH_);
	}
	catch(std::exception)
	{
		QMessageBox::warning(this,tr("警告"),tr("写入硬件错误，请检查USB模块！"),QMessageBox::Yes);
		ui.informationEdit->insertPlainText( QTime::currentTime().toString("[hh:mm:ss]")+"\tWrite Hardware failed!\n");
		ui.informationEdit->moveCursor(QTextCursor::End);
		return;
	}
	ui.informationEdit->insertPlainText(QTime::currentTime().toString("[hh:mm:ss]") + "\t出洞\t--\n");
	ui.informationEdit->moveCursor(QTextCursor::End);
	bIsPressOutholeButton_ = true;
	bIsPressInholeButton_ = false;
}


/* 
 @brief 菜单About 
*/
void LZ_MainWindow::onActionAbout()
{
	QMessageBox::about(this, tr("About 进出洞检测程序"),
		tr("<h2>version 1.0</h2>"
		   "<p>Copyright &copy; 2015 ...."
		   "<p>进出洞检测程序连接到主控和白盒，用于控制和发送进出洞信号"
		   "<p>有三种工作模式可供选择， 手动模式，自动模式及自由触发模式"
		   "<p>手动模式下可点击进洞按钮和出洞按钮以及键盘'+'键和'Enter'键控制"
		   "<p>自动模式下打开激光器和两个相机， 自动确定进出洞状态，自由触发模式用于测试。"));

}
/*
 @brief 菜单Exit 
 */
void LZ_MainWindow::onActionExit()
{
	this->~LZ_MainWindow();
}

/*
 @brief 相机传回的异常 
 */
void LZ_MainWindow::receiveException(const char *msg)
{
	qDebug() << msg;
	ui.informationEdit->insertPlainText(QTime::currentTime().toString("[hh:mm:ss]\t") + tr(msg));
	pAutoDetectThread_->stop();
	QMessageBox::warning(this, tr("错误！"), tr(msg), QMessageBox::Yes);
}

/** 
 * @brief 自动模式传回的进出洞信号 
 */
void LZ_MainWindow::receiveStatus(bool isPreInHole,bool isInHole, int time_ms,
	double leftDis, double rightDis)
{
	qDebug() << "main received status from autodetect ";
	/*if(bIsPreInHole_ == isPreInHole && bIsInHole_ == isInHole)
		return;*/
	/*
	使用两位标记三个状态
	P(bIsPreInHole)I(bIsInHole):
	 00 出洞, 10 预进洞,  11 进洞
			 出洞 _
		   //    |\ 
		 预进洞 -> 进洞
	*/
	bIsInHole_ = isInHole;
	bIsPreInHole_ = isPreInHole;
	/*  写硬件到A和M_PC */
	vBitsWriteToA_IOH_[6] = isInHole;    
	vBitsWriteToMPC_IOH_[0] = isPreInHole;
	vBitsWriteToMPC_IOH_[1] = isInHole;
	try
	{
		pWriteToA_IOH_->write(vBitsWriteToA_IOH_);
		pWriteToMPC_IOH_->write(vBitsWriteToMPC_IOH_);
	}
	catch(...)
	{
		QMessageBox::warning(this, tr("错误！"), tr("写入硬件错误!"), QMessageBox::Yes);
		ui.hardwareEdit->setText("失败");
		if(pAutoDetectThread_->isRunning())
			pAutoDetectThread_->stop();
		return;
	}
	// UI display
	QString display;
	if( bIsPreInHole_ == true && bIsInHole_ == false )  // 10
	{
		ui.inOutHoleLabel->setPixmap(QPixmap(":/resource/lightpreinhole.png"));
		display ="\t预进洞";
	}
	else if(bIsPreInHole_ == true && bIsInHole_ == true) // 11
	{
		ui.inOutHoleLabel->setPixmap(QPixmap(":/resource/lightinhole.png"));
		display = "\t进洞 ";
	}
	else if(bIsPreInHole_ == false && bIsInHole_ == false)  // 00
	{
		ui.inOutHoleLabel->setPixmap(QPixmap(":/resource/lightouthole.png"));
		display = "\t出洞 ";
	}
	else  // 不会到该分支，在InOutStatus.cpp中做了判断
	{
		return;
	}
	display = QTime::currentTime().toString("[hh:mm:ss]") + display;
	ui.informationEdit->insertPlainText( display);
	ui.informationEdit->moveCursor(QTextCursor::End);
	/*ui.lefttDistanceEdit->setText(leftDis);
	ui.rightDistanceEdit->setText(rightDis);
	ui.leftTimeEdit->setText();*/
}

/*@brief 自动模式传回的图像 */
void LZ_MainWindow::receiveImg(const QImage & qImg,bool is_left)
{
	QImage smallLeftImg = qImg.scaled(100, 150, Qt::IgnoreAspectRatio,Qt::FastTransformation);
	if(is_left)
	{
		ui.leftImgLabel->setPixmap(QPixmap::fromImage(smallLeftImg));
		ui.leftImgLabel->show();
	}
	else
	{
		ui.rightImgLabel->setPixmap(QPixmap::fromImage(smallLeftImg));
		ui.rightImgLabel->show();
	}
}

/*  @brief 工作模式转化为  */
QString LZ_MainWindow::strategyToStr()
{
	switch(workMode_)
	{
	case WKM_AUTO:
		return QString("自动模式");
	case WKM_MANUAL:
		return QString("手动模式");
	case WKM_TESTING:
		return QString("自由触发");
	default:
		return QString("");
	}
	return QString("");
}

LZ_MainWindow::~LZ_MainWindow()
{
	if(pAutoDetectThread_->isRunning())
		pAutoDetectThread_->stop();
	if(pReadHardWareThread_->isRunning())
		pReadHardWareThread_->stop();
	onSetOutHoleButton();
	delete pAutoDetectThread_;
	delete pWriteToA_IOH_;
	delete pWriteToMPC_IOH_;
	delete pWriteToA_FromMPC_;
	delete pReadFromMPC_;
	delete pReadHardWareThread_;
}


