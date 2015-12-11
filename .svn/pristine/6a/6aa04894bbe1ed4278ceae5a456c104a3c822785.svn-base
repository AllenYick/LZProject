/*/////////////////////////////////////////////////////////
*
*	CameraImageEventHandler.h
*	相机采集事件处理文件
*
*//////////////////////////////////////////////////////////

#ifndef LZCAMERAIMAGEEVENTHANDLER_H
#define LZCAMERAIMAGEEVENTHANDLER_H

#include <opencv2\opencv.hpp>

using namespace cv;

#include <pylon/PylonIncludes.h>
#include <pylon/PylonGUI.h>
#include <pylon/ImageEventHandler.h>
#include <pylon/GrabResultPtr.h>

#include <QObject>
#include <QtCore\QDebug>
#include <QtCore\QMutex>
#include <QtGui\QImage>

#include "CameraConfiguration.h"
#include "DataModel.h"
#include "InOutStatus.h"
#include "TriangleDistance.h"

class LzCameraAcquisition;
using namespace Pylon;

using namespace Basler_GigECameraParams;

namespace Pylon
{

class CBaslerGigEInstantCamera;

class ImageEventHandler : public CBaslerGigEImageEventHandler
{
public:
	// 
	virtual void OnImageGrabbed( CBaslerGigEInstantCamera& camera, const CBaslerGigEGrabResultPtr& ptrGrabResult) override;

	ImageEventHandler( ) { 
		grabImg.create(FRAME_ROWS, FRAME_COLS, CV_8UC1);
		m = DataModel::getInstance();
	}

	void tieHoudlerAndCamera( LzCameraAcquisition* _holder, CBaslerGigEInstantCamera *_cam )
	{
		cameraholder = _holder;
		camera = _cam;
		camera_id = _cam->GetDeviceInfo().GetSerialNumber();
	}

	QImage MatToQImage(const Mat& mat);

private:

	QMutex mutex;
	// cameraholder
	LzCameraAcquisition *cameraholder;
	// 绑定的相机id
	Pylon::String_t camera_id;
	// 绑定的相机
	CBaslerGigEInstantCamera *camera;

	Mat grabImg;
	DataModel *m;

};



}

#endif /* LZCAMERAIMAGEEVENTHANDLER_H */
