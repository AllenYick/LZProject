#include "AutoDetectThread.h"
#define FRAME_FREQ  2

AutoDetectThread::AutoDetectThread()
{
	stopped_ = false;
	initialized_ = false;
	lzCameraAcquisition_ = new LzCameraAcquisition(NUM_CAMERAS);
	inouttunnel_status_ = InOutTunnelStatus::getInstance();
	m_tridistance.clear();
	m_tridistance.resize(NUM_CAMERAS, NULL);
}

AutoDetectThread::~AutoDetectThread()
{
	lzCameraAcquisition_->stopGrabbing();
	delete  lzCameraAcquisition_;
	delete  inouttunnel_status_;
}
/*
 /*
 @brief
    初始化相机采集对象并配置相机
*/
void AutoDetectThread::init()
{
	if( initialized_ == true )
		return;
	for(int j = 0; j < 5; j++)
	{
		try
		{
			lzCameraAcquisition_->init();
			lzCameraAcquisition_->cfgExposureTime(EXPOSURE_TIME);
			lzCameraAcquisition_->cfgImageEventHandler();
			lzCameraAcquisition_->cfgTriggerMode(AM_SOFTWARE);     // 配置相机的采集模式
			lzCameraAcquisition_->openCamera();
			lzCameraAcquisition_->startGrabbing();
		}
		catch(...)
		{
			continue;
		}
		for( int i = 0; i < NUM_CAMERAS; i++)
		{
			index_to_id_[i] = lzCameraAcquisition_->index_to_id[i];
			m_tridistance[i] = new TriangleDistance(index_to_id_[i]);

			id_to_index[index_to_id_[i]] = i;
		}
		initialized_ = true;
		return;
	}
	throw LzException( 4, "相机初始化失败！");
}
/*
 @brief
    运行进程
*/
void AutoDetectThread::run()
{
	uint32_t count = 1;
	char filename[100];   // 文件名
	DataModel *m = DataModel::getInstance();
	//_mkdir("F:\\XXX"); // 创建文件夹
	while( true )
	{
		stopMutex_.lock();
		if(stopped_)
		{
			stopped_ = false;
			stopMutex_.unlock();
			break;
		}
		stopMutex_.unlock();
		DWORD timeelapse_ms = ::GetTickCount();
		///////////////////////////////////
		// 工作在软触发模式
		lzCameraAcquisition_->cameras[0].ExecuteSoftwareTrigger();
		lzCameraAcquisition_->cameras[1].ExecuteSoftwareTrigger();
		///////////////////////////////////
		while(!(m->hasLeftGrabed) || (!m->hasRightGrabed))
			::Sleep(5);
		if(m->hasLeftGrabed  && m->hasRightGrabed)
		{
			//initial images
			m_tridistance[id_to_index[SN_LEFT]]->init(m->mats[m->id_to_index[SN_LEFT]]);
			m_tridistance[id_to_index[SN_RIGHT]]->init(m->mats[m->id_to_index[SN_RIGHT]]);
			// compute distances
			distances_[id_to_index[SN_LEFT]] = m_tridistance[m->id_to_index[SN_LEFT]]->compute();
			distances_[id_to_index[SN_RIGHT]] = m_tridistance[m->id_to_index[SN_RIGHT]]->compute();
			// in out tunnel status
			inouttunnel_status_->process(distances_, NUM_CAMERAS);

			qDebug() << "process successed!";
			m->hasLeftGrabed = false;
			m->hasRightGrabed = false;
			count++;
			if(count % FRAME_FREQ == 0)
			{
				emit sendImg(m->qImages[m->id_to_index[SN_LEFT]], true);
				emit sendImg(m->qImages[m->id_to_index[SN_RIGHT]], false);
			}
			qDebug() << "autodetect send  to main";
			int current_state = (int)inouttunnel_status_->getState();
			timeelapse_ms = ::GetTickCount() - timeelapse_ms;
			emit sendStatus((current_state>>1)&1, current_state&1, timeelapse_ms, 
				distances_[id_to_index[SN_LEFT]], distances_[id_to_index[SN_RIGHT]]);   // send to main thread
		}	
	}
}

/*
 @brief
    关闭进程
*/
void AutoDetectThread::stop()
{
	stopMutex_.lock();
	stopped_ = true;
	stopMutex_.unlock();
}


