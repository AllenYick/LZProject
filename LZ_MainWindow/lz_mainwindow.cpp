#include "lz_mainwindow.h"
#include "LZCamera.h"
#include <fstream>

LZ_MainWindow::LZ_MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	// ��ʼ����ʾͼƬ
	ui.hardwareEdit->setPixmap(QPixmap(":/resource/cross.png"));       // ��ʾͼƬ
	ui.cameraStatusLabel->setPixmap(QPixmap(":/resource/collectstatus1_2.png"));
	ui.inOutHoleLabel->setPixmap(QPixmap(":/resource/lightouthole.png"));
	// ��ʼ������
	bIsPressInholeButton_ = false;
	bIsPressOutholeButton_ = false;
	bIsInitCamera_ = false;
	bIsInitHardware_ = false;
	workMode_ = WKM_MANUAL;           // Ĭ���ֶ�ģʽ
	bIsReadFromMPC_ = false;
	bIsInHole_ = false;
	bIsPreInHole_ = false;           // Ĭ�ϳ���
	vBitsReadFromMPC_.resize(NUM_BITS, false);
	vBitsWriteToA_FromMPC_.resize(NUM_BITS, false);
	vBitsWriteToA_IOH_.resize(NUM_BITS, false);
	vBitsWriteToMPC_IOH_.resize(NUM_BITS, false);
	
	// ��ʼ���Զ�������
	pAutoDetectThread_ = new AutoDetectThread();
	
	// ��ʼ����дӲ��ָ��
	pReadHardWareThread_ = new ReadHardwareThread(PORT_NUM_READ_FROM_MPC, NUM_BITS);
	pWriteToMPC_IOH_ = new WriteHardware(PORT_NUM_WRITE_TO_MPC, NUM_BITS);
	pWriteToA_IOH_ = new WriteHardware(PORT_NUM_WRITE_IOH_TO_A, NUM_BITS);    
	pWriteToA_FromMPC_ = new WriteHardware(PORT_NUM_WRITE_TO_A, NUM_BITS);

	/* ���ý�������ݷ�ʽ��'+'������'Enter'���� */
	ui.setInHoleButton->setShortcut(Qt::Key_Plus);
	ui.setOutHoleButton->setShortcut(Qt::Key_Enter);
	// �����ź����
	// for button
	connect(ui.setInHoleButton, SIGNAL(clicked()), this, SLOT(onSetInHoleButton()));
	connect(ui.setOutHoleButton, SIGNAL(clicked()), this, SLOT(onSetOutHoleButton()));
	connect(ui.initCameraButton, SIGNAL(clicked()), this, SLOT(initCameras()));
	//for action
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(onActionAbout()));  
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(onActionExit()));
	// for signal
	// @brief  �Զ������̷��صĽ������ź� 
	connect(pAutoDetectThread_, SIGNAL(sendStatus(bool,bool,int, double, double)), this, 
		SLOT(receiveStatus(bool,bool,int, double, double)));
	// @brief  �Զ������̷��ص��쳣�ź� 
	connect(pAutoDetectThread_, SIGNAL(sendException(const char *)), this, SLOT(receiveException(const char *)), Qt::DirectConnection);
	// @brief  �Զ������̷�����ʾͼ�����Ϣ 
	connect(pAutoDetectThread_, SIGNAL(sendImg(const QImage &,bool)), this, SLOT(receiveImg(const QImage &,bool)));
	// @brief  �ı乤��ģʽ���ص���Ϣ 
	connect(pReadHardWareThread_, SIGNAL(sendModeChange(bool, bool, bool, bool)), this, SLOT(receiveModeChange(bool, bool, bool, bool)), Qt::DirectConnection);

	ui.setOutHoleButton->setEnabled(false);
	// ��ʼ��Ӳ�� readHardwareThread,writeToM_PC,writeToA�� ������M_PC�������ź�
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
		QMessageBox::warning(this,tr("����"),tr("δ��Ӳ����"),QMessageBox::Yes);
		return;
	}
	bIsInitHardware_ = true;
	ui.hardwareEdit->setPixmap(QPixmap(":/resource/ok.png"));       // ��ʾͼƬ            
}

/*
  �ı乤��ģʽ
*/
void LZ_MainWindow::receiveModeChange(bool b0, bool b1, bool b2, bool b3)
{
	vBitsReadFromMPC_[0] = b0;
	vBitsReadFromMPC_[1] = b1;
	vBitsReadFromMPC_[2] = b2;
	vBitsReadFromMPC_[3] = b3;

	if((vBitsReadFromMPC_[0] == 1) && (vBitsReadFromMPC_[1]==0))      // 10:���ɴ���
		workMode_ = WKM_TESTING;
	else if((vBitsReadFromMPC_[0] == 0) && (vBitsReadFromMPC_[1]==1)) // 01:�Զ�
		workMode_ = WKM_AUTO;
	else                                                              // 00:�ֶ�
		workMode_ = WKM_MANUAL;
	QString display =QTime::currentTime().toString("[hh:mm:ss]")+"\t��ȡ������M_PC����Ϣ,";
	display += "\t����ģʽΪ:"+ strategyToStr() + "\n";
	display += QString("\t״̬Ϊ:%1 %2\n").arg(vBitsReadFromMPC_[2]).arg(vBitsReadFromMPC_[3]);
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
	 P1��:д��A
		| D5:���ɴ���ģʽλ��1����Ч
		| D6:������λ       1����Ч
	*/
	vBitsWriteToA_IOH_[5] = (workMode_==WKM_TESTING); // ���ɴ���λ   
	vBitsWriteToA_IOH_[6] = 0;                      // ������λ��Ĭ�ϳ���

	/*
	P5��:д��M_PC 
	   |  D0D1 Ϊ������״̬,Ĭ�ϳ���
	      00(0)������  10(2)��Ԥ����  11(3)������
	*/ 
	vBitsWriteToMPC_IOH_[0] = 0;        // S0
	vBitsWriteToMPC_IOH_[1] = 0;        // S1     
	pWriteToMPC_IOH_->write(vBitsWriteToMPC_IOH_);
	/*
	 P2��:д��A��ת������M_PC����Ϣ
	    | D7D6:���ɴ���ģʽ
	       00:30Hz 01:50Hz  10:40Hz 11: 60Hz
	    | D5: �Զ����λ  0:��Ч  1:��Ч
	*/
	vBitsWriteToA_FromMPC_[7] = vBitsReadFromMPC_[2];
	vBitsWriteToA_FromMPC_[6] = vBitsReadFromMPC_[3];
	vBitsWriteToA_FromMPC_[5] = !(workMode_ == WKM_AUTO);  // �Զ����λ����λ��Ч
	ui.modeEdit->setText(strategyToStr());
	pWriteToA_FromMPC_->write(vBitsWriteToA_FromMPC_);
	pWriteToA_IOH_->write(vBitsWriteToA_IOH_);

	if(workMode_ == WKM_AUTO )
	{
		ui.setInHoleButton->setEnabled(false);
		ui.setOutHoleButton->setEnabled(false);
		if(bIsInitCamera_ == false)
		{
			ui.informationEdit->insertPlainText(QTime::currentTime().toString("[hh:mm:ss]") + "\t���δ��ʼ�������ܹ������Զ�ģʽ\n");
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
 ��ʼ�����
*/
void LZ_MainWindow::initCameras()
{
	if(bIsInitCamera_ == true)
		return;
	ui.informationEdit->insertPlainText(QTime::currentTime().toString("[hh:mm:ss]")+"\t���ڳ�ʼ�����...\n");
		
	try
	{
		pAutoDetectThread_->init();
	}
	catch (LzException& e)
	{
		qDebug() << e.what();
		ui.informationEdit->insertPlainText(QTime::currentTime().toString("[hh:mm:ss]")+QString("\t��ʼ�����ʧ��\n"));
		QMessageBox::warning(this,tr("����"),tr("δ�������"),QMessageBox::Yes);
		return;
	}
	ui.informationEdit->insertPlainText(QTime::currentTime().toString("[hh:mm:ss]")+"\t��ʼ������ɹ�\n");
	ui.cameraStatusLabel->setPixmap(QPixmap(":/resource/collectstatus1.png"));
	bIsInitCamera_ = true;
}

/**
 *  @brief �ֶ�ģʽ����
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
		QMessageBox::warning(this,tr("����"),tr("д��Ӳ����������USBģ�飡"),QMessageBox::Yes);
		ui.informationEdit->insertPlainText( QTime::currentTime().toString("[hh:mm:ss]")+"\tWrite Hardware failed!\n");
		ui.informationEdit->moveCursor(QTextCursor::End);
		return;
	}
	ui.informationEdit->insertPlainText(QTime::currentTime().toString("[hh:mm:ss]") + "\t����\t--\n");
	ui.informationEdit->moveCursor(QTextCursor::End);
	bIsPressInholeButton_ = true;
	bIsPressOutholeButton_ = false;
}

/**
 *  @brief �ֶ�ģʽ����
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
		QMessageBox::warning(this,tr("����"),tr("д��Ӳ����������USBģ�飡"),QMessageBox::Yes);
		ui.informationEdit->insertPlainText( QTime::currentTime().toString("[hh:mm:ss]")+"\tWrite Hardware failed!\n");
		ui.informationEdit->moveCursor(QTextCursor::End);
		return;
	}
	ui.informationEdit->insertPlainText(QTime::currentTime().toString("[hh:mm:ss]") + "\t����\t--\n");
	ui.informationEdit->moveCursor(QTextCursor::End);
	bIsPressOutholeButton_ = true;
	bIsPressInholeButton_ = false;
}


/* 
 @brief �˵�About 
*/
void LZ_MainWindow::onActionAbout()
{
	QMessageBox::about(this, tr("About ������������"),
		tr("<h2>version 1.0</h2>"
		   "<p>Copyright &copy; 2015 ...."
		   "<p>���������������ӵ����غͰ׺У����ڿ��ƺͷ��ͽ������ź�"
		   "<p>�����ֹ���ģʽ�ɹ�ѡ�� �ֶ�ģʽ���Զ�ģʽ�����ɴ���ģʽ"
		   "<p>�ֶ�ģʽ�¿ɵ��������ť�ͳ�����ť�Լ�����'+'����'Enter'������"
		   "<p>�Զ�ģʽ�´򿪼���������������� �Զ�ȷ��������״̬�����ɴ���ģʽ���ڲ��ԡ�"));

}
/*
 @brief �˵�Exit 
 */
void LZ_MainWindow::onActionExit()
{
	this->~LZ_MainWindow();
}

/*
 @brief ������ص��쳣 
 */
void LZ_MainWindow::receiveException(const char *msg)
{
	qDebug() << msg;
	ui.informationEdit->insertPlainText(QTime::currentTime().toString("[hh:mm:ss]\t") + tr(msg));
	pAutoDetectThread_->stop();
	QMessageBox::warning(this, tr("����"), tr(msg), QMessageBox::Yes);
}

/** 
 * @brief �Զ�ģʽ���صĽ������ź� 
 */
void LZ_MainWindow::receiveStatus(bool isPreInHole,bool isInHole, int time_ms,
	double leftDis, double rightDis)
{
	qDebug() << "main received status from autodetect ";
	/*if(bIsPreInHole_ == isPreInHole && bIsInHole_ == isInHole)
		return;*/
	/*
	ʹ����λ�������״̬
	P(bIsPreInHole)I(bIsInHole):
	 00 ����, 10 Ԥ����,  11 ����
			 ���� _
		   //    |\ 
		 Ԥ���� -> ����
	*/
	bIsInHole_ = isInHole;
	bIsPreInHole_ = isPreInHole;
	/*  дӲ����A��M_PC */
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
		QMessageBox::warning(this, tr("����"), tr("д��Ӳ������!"), QMessageBox::Yes);
		ui.hardwareEdit->setText("ʧ��");
		if(pAutoDetectThread_->isRunning())
			pAutoDetectThread_->stop();
		return;
	}
	// UI display
	QString display;
	if( bIsPreInHole_ == true && bIsInHole_ == false )  // 10
	{
		ui.inOutHoleLabel->setPixmap(QPixmap(":/resource/lightpreinhole.png"));
		display ="\tԤ����";
	}
	else if(bIsPreInHole_ == true && bIsInHole_ == true) // 11
	{
		ui.inOutHoleLabel->setPixmap(QPixmap(":/resource/lightinhole.png"));
		display = "\t���� ";
	}
	else if(bIsPreInHole_ == false && bIsInHole_ == false)  // 00
	{
		ui.inOutHoleLabel->setPixmap(QPixmap(":/resource/lightouthole.png"));
		display = "\t���� ";
	}
	else  // ���ᵽ�÷�֧����InOutStatus.cpp�������ж�
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

/*@brief �Զ�ģʽ���ص�ͼ�� */
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

/*  @brief ����ģʽת��Ϊ  */
QString LZ_MainWindow::strategyToStr()
{
	switch(workMode_)
	{
	case WKM_AUTO:
		return QString("�Զ�ģʽ");
	case WKM_MANUAL:
		return QString("�ֶ�ģʽ");
	case WKM_TESTING:
		return QString("���ɴ���");
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

