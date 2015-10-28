/****************************************************************
*	LzCamera.h
* @brief 
*   image acquisition 
* @params
*   distance
* @author   Yike    
*          2015.06.10
*****************************************************************/

#ifndef LZ_CAMERA_H
#define LZ_CAMERA_H

#include <QObject>
#include <pylon/PylonIncludes.h>
#include <pylon/gige/BaslerGigeInstantCameraArray.h>

#include "LzCommon.h"
#include "CameraConfiguration.h"
#include "CameraImageEventHandler.h"

// Namespace for using pylon objects.
using namespace Pylon;


class LzCameraAcquisition  
{
public:
	LzCameraAcquisition(int numd):numdevices(numd){};

	// initial cameras 
	void init();

	// set exposure time  
	void cfgExposureTime(int exposure_time = EXPOSURE_TIME);

	// config image event handler  
	void cfgImageEventHandler();

	// set acquisition mode 
	void cfgTriggerMode(AcquiMode mode);

	// @brief   open the cameras and the cameras will enter acquisition status 
	void openCamera();

	// @brief  start grabbing 
	void startGrabbing();

	// @brief  stop grabbing 
	void stopGrabbing();

public:
	CBaslerGigEInstantCameraArray cameras;
	AcquiMode mode;
	std::map<int, Pylon::String_t>  index_to_id;
	std::vector<ImageEventHandler*> imghandlers;

private:
	PylonAutoInitTerm autoInitTerm;
	size_t numdevices;
};

#endif