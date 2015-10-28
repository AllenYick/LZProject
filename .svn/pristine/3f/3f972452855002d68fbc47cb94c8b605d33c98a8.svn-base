/****************************************************************

*****************************************************************/

#ifndef AUTODETECTINOUTHOLETHREAD_H
#define AUTODETECTINOUTHOLETHREAD_H

#include <opencv2\opencv.hpp>
#include <QtCore\QThread>
#include <QtCore\QDebug>
#include <QtCore\QMutex>
#include <QtGui>

#include "LZCamera.h"
#include "LzException.h"
#include "LzCommon.h"


class CameraThread : public QThread
{
	Q_OBJECT
public:
	CameraThread();
	~CameraThread();
	void init();
	void stop();
	QImage CameraThread::MatToQImage();
	Mat mat;
	QImage qImg;

private:
	LzCameraAcquisition*           lzCameraAcquisition;
	bool                              m_bInitialized;
	volatile bool                  stopped;
	QMutex                         mutex;

protected:
	void run();

signals:
	void sendException(const char *);
	void sendImg(const QImage& qImg);
};

#endif