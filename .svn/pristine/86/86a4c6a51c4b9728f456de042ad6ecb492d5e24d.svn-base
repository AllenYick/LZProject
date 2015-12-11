#ifndef ACQUTEST_H
#define ACQUTEST_H

#include <QtGui/QMainWindow>
#include "ui_acqutest.h"
#include "LZCamera.h"
#include "cameraThread.h"

class AcquTest : public QMainWindow
{
	Q_OBJECT

public:
	AcquTest(QWidget *parent = 0, Qt::WFlags flags = 0);
	~AcquTest();

	

public slots:
	void onBegin();
	void receiveImg(const QImage & qImg);
	
private:
	Ui::AcquTestClass ui;

	CameraThread* pCameraThread;
};

#endif // ACQUTEST_H
