/****************************************************************
*	CameraConfiguration.h
* @brief 
*   configuration head file of two cameras .
*   include exposure time, trigger mode...
* @params
*   已初始化相机

* @author   Yike    
*          2015.06.10
*****************************************************************/

#ifndef LZCAMERACONFIGURATION_H
#define LZCAMERACONFIGURATION_H

#include <pylon/gige/BaslerGigEInstantCamera.h>
#include <pylon/ConfigurationEventHandler.h>

#include <iostream>
#include <map>

#include "LZCommon.h"

#define ROI_WIDTH          (1280)
#define ROI_HEIGHT         (1024)
#define EXPOSURE_TIME      (5000)
#define CAMERA_BUFFER      (10)

namespace Pylon
{
	class CInstantCamera;

	using namespace Basler_GigECameraParams;

	class CameraRegularConfiguration : public Pylon::CBaslerGigEConfigurationEventHandler
	{
	public:    
		void OnOpened( Pylon::CBaslerGigEInstantCamera& camera);
		CameraRegularConfiguration(unsigned int _exposure_time = EXPOSURE_TIME)
			: exposure_time(_exposure_time) {}

	private: 
		unsigned int exposure_time;
	};

	class CHardwareTriggerConfiguration : public Pylon::CBaslerGigEConfigurationEventHandler
	{
	public:
		void OnOpened( Pylon::CBaslerGigEInstantCamera& camera);
	};

	class CLzSoftwareTriggerConfiguration : public Pylon::CBaslerGigEConfigurationEventHandler
	{
	public:
		void OnOpened( Pylon::CBaslerGigEInstantCamera& camera);
	};

}
#endif 