#include "cameraThread.h"

#define SAVE_IMG false

CameraThread::CameraThread()
{
	stopped = false;
	m_bInitialized = false;
	lzCameraAcquisition = new LzCameraAcquisition(2);
	mat.create(FRAME_ROWS, FRAME_COLS, CV_8UC1);
}

CameraThread::~CameraThread()
{
	lzCameraAcquisition->stopGrabbing();
	//lzCameraAcquisition->stop()
	delete  lzCameraAcquisition;
}

void CameraThread::init()
{
	if( m_bInitialized == true )
		return;
	try
	{
		lzCameraAcquisition->init();
		lzCameraAcquisition->cfgEventHandler( true, EXPOSURE_TIME);
		lzCameraAcquisition->cfgTriggerMode(AM_HARDWARE);     // 配置相机的采集模式
		lzCameraAcquisition->openCamera();
	}
	catch(...)
	{
		throw LzException(4, "Open camera failed");
	}
	m_bInitialized = true;
}

void CameraThread::run()
{
	int count = 1;
	while( true )
	{
		mutex.lock();
		if(stopped)
		{
			stopped = false;
			mutex.unlock();
			break;
		}
		mutex.unlock();
		std::vector<char *> grabBuffer;
		try
		{
			for(int i = 0; i < 1; i++)
				grabBuffer = lzCameraAcquisition->grabOne();
		}
		catch (LzException& e)
		{
			qDebug() << e.what();
			emit sendException(e.what());
			return;
		}
		memcpy(mat.data, grabBuffer[0], FRAME_SIZE);
		qImg = MatToQImage();
		/*if(SAVE_IMG)
		{
			char filename[100];
			for(int i = 0; i <NUM_CAMERA; i++)
			{
				string file = string("F:\\0627_2\\")+indexToid[i].toStdString() + string("_%d.png");
				sprintf(filename,file.c_str(),count);
				m_tridistance[i]->img_for_process->saveImg(filename);
			}
		}*/
		if( (count % 11) == 0)
			emit sendImg(qImg);
		qDebug() << "autodetect send  to main";
		count++;
	}
}

QImage CameraThread::MatToQImage()
{
	// 8-bits unsigned, NO. OF CHANNELS=1
	if(mat.type()==CV_8UC1)
	{
		// Set the color table (used to translate colour indexes to qRgb values)
		QVector<QRgb> colorTable;
		for (int i=0; i<256; i++)
			colorTable.push_back(qRgb(i,i,i));
		// Copy input Mat
		const uchar *qImageBuffer = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
		img.setColorTable(colorTable);
		return img;
	}
	// 8-bits unsigned, NO. OF CHANNELS=3
	if(mat.type()==CV_8UC3)
	{
		// Copy input Mat
		const uchar *qImageBuffer = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return img.rgbSwapped();
	}
	else
	{
		qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}
}

void CameraThread::stop()
{
	mutex.lock();
	stopped = true;
	mutex.unlock();
}


