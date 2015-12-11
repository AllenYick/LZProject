#include "acqutest.h"

AcquTest::AcquTest(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	pCameraThread = new CameraThread();

	//
	connect(ui.cameraButton, SIGNAL(clicked()), this, SLOT(onBegin()));
	connect(pCameraThread, SIGNAL(sendImg(const QImage&)), this, SLOT(receiveImg(const QImage&)));
}

void AcquTest::onBegin()
{
	pCameraThread->init();
	pCameraThread->start();
}

void AcquTest::receiveImg(const QImage& qImg)
{
	//Mat temp;
	//temp.copyTo(leftMat);
	///*imshow("", leftImg);
	//waitKey(10);*/
	//QImage leftImg = MatToQImage(leftMat);
	//qDebug() << leftImg.size();
	//QImage smallLeftImg = leftImg.scaled(100, 150, Qt::IgnoreAspectRatio,Qt::FastTransformation);
	//ui.leftImgLabel->setPixmap(QPixmap::fromImage(smallLeftImg));
	//ui.leftImgLabel->show();
	qDebug() << qImg.size();
	QImage smallLeftImg = qImg.scaled(100, 150, Qt::IgnoreAspectRatio,Qt::FastTransformation);
	ui.imgLabel->setPixmap(QPixmap::fromImage(smallLeftImg));
	ui.imgLabel->show();
}

AcquTest::~AcquTest()
{
	pCameraThread->stop();
}
