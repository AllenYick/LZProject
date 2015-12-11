#include "LzCamera.h"
#include  "LzException.h"

/*
 @brief
    initial cameras
*/
void LzCameraAcquisition::init() 
{
	DeviceInfoList_t devices;
	try
	{
		CTlFactory& tlFactory = CTlFactory::GetInstance();

		tlFactory.EnumerateDevices( devices );

		if ( devices.empty() )
		{
			throw LzException( 3, "No camera present.");
		}
		else if( devices.size()!=numdevices )
		{
			throw LzException( 4, "Not enough camera present.");
		}
		try
		{
			cameras.Initialize( numdevices );
		}
		catch(...)
		{
			throw LzException(3, "Initialize camera failed");
		}
		cameras.DestroyDevice();

		// 为相机实例添加设备
		DataModel* m = DataModel::getInstance();
		for ( size_t i = 0; i < numdevices; i++)
		{
			cameras[i].Attach( tlFactory.CreateDevice( devices[i] ) );
			index_to_id[i] = cameras[i].GetDeviceInfo().GetSerialNumber();
			m->id_to_index[index_to_id[i]] = i;
		}
	}
	catch(LzException& ex)
	{
		throw ex;
	}
	catch(...)
	{
		throw LzException(3, "Attach error");
	}
	// initialize imghandlers
	imghandlers.resize(numdevices);
	for ( size_t i = 0; i < numdevices; i++)
	{
		imghandlers[i] = new ImageEventHandler();
	}
	return;
}// init

/*
 @brief
    配置相机曝光时间
 @param [in]
    exposure_time : 曝光时间
*/
void LzCameraAcquisition::cfgExposureTime(int exposure_time)
{
	try
	{
		for (int i = 0; i <numdevices; i++)
		{
			cameras[i].RegisterConfiguration( new CameraRegularConfiguration(exposure_time), 
				RegistrationMode_ReplaceAll, Cleanup_Delete );
		}
	}
	catch(std::exception &e)
	{
		throw LzException(5, "Set exposure time error");
	}
}

/*
 @brief
    配置相机图片处理事件（image event handler）
*/
void LzCameraAcquisition::cfgImageEventHandler() 
{
	try
	{
		for (int i = 0; i <numdevices; i++)
		{
			cameras[i].RegisterImageEventHandler(imghandlers[i], RegistrationMode_Append, Cleanup_None);
			imghandlers[i]->tieHoudlerAndCamera(this, &(cameras[i]));
		}
	}
	catch(std::exception &e)
	{
		throw LzException(5, "Set exposure time error");
	}
}

/*
 @brief
    配置相机采集模式
 @param [in]
	mode: 采集模式，有连续采集，硬触发和软触发
*/
void LzCameraAcquisition::cfgTriggerMode(AcquiMode mode) 
{
	this->mode = mode;

	if ( mode == AM_SOFTWARE )
	{
		for (int i=0; i<numdevices; i++)
		{
			cameras[i].RegisterConfiguration( new CLzSoftwareTriggerConfiguration, 
											RegistrationMode_Append, 
											Cleanup_Delete);
		}
	}
	else if (mode == AM_HARDWARE )
	{
		for (int i=0; i<numdevices; i++)
		{
			cameras[i].RegisterConfiguration( new CHardwareTriggerConfiguration,
											RegistrationMode_Append,
											Cleanup_Delete );
		}
	}
	else if (mode == AM_CONTINUE )
	{
		for (int i=0; i<numdevices; i++)
		{
			cameras[i].RegisterConfiguration( new CAcquireContinuousConfiguration, 
											RegistrationMode_Append,
											Cleanup_Delete);
		}
	}
}

/*
 @brief
    打开相机
*/
void LzCameraAcquisition::openCamera()
{
	try
	{
		for (size_t i = 0; i < numdevices; i++)
			cameras[i].Open();
	}
	catch(std::exception &ex)
	{
		throw LzException(4, "Open Camera failed!");
	}
}

/*
 @brief
    开始采集
*/
void LzCameraAcquisition::startGrabbing()
{
	try{
		for ( size_t i=0; i<numdevices; i++ )
			cameras[i].StartGrabbing(GrabStrategy_OneByOne,GrabLoop_ProvidedByInstantCamera);
	}
	catch(std::exception &ex)
	{
		throw LzException(4, "Start grabing Camera failed!");
	}
}

/*
 @brief
    停止采集
*/
void LzCameraAcquisition::stopGrabbing()
{		
	for (int i=0; i<numdevices; i++)
	{
		cameras[i].StopGrabbing();
	}
}

