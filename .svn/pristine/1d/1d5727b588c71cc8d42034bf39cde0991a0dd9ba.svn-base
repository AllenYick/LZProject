/****************************************************************
**AutoDetectThread.h
* @brief 
*   detect the state of train, out-hole, prein-hole or in-hole,
*	work in AUTO mode
*
* @params
*    the port's number and bits to read

* @author   Yike    
*          2015.06.10
*****************************************************************/

#ifndef AUTODETECTINOUTHOLETHREAD_H
#define AUTODETECTINOUTHOLETHREAD_H

#include <QtCore\QThread>
#include <QtCore\QDebug>
#include <QtCore\QMutex>
#include <QtGui>
#include <map>

#include "LzCamera.h"
#include "InOutStatus.h"
#include "TriangleDistance.h"
#include "LzException.h"
#include "LzCommon.h"
#include "DataModel.h"

class AutoDetectThread : public QThread
{
	Q_OBJECT
public:
	AutoDetectThread();
	~AutoDetectThread();
	void init();
	void stop();
public:
	// 对应到每个相机的三角距离计算对象
	vector<TriangleDistance*>      m_tridistance;   
	std::map<Pylon::String_t, int> id_to_index;
	
private:
	// 采集对象
	LzCameraAcquisition*           lzCameraAcquisition_;
	// 三角距离【out】
	double                         distances_[NUM_CAMERAS];
	// 进出洞状态管理对象
	InOutTunnelStatus*             inouttunnel_status_;
	// 相机编号与ID映射
	std::map<int, Pylon::String_t> index_to_id_;         
	bool                           initialized_;
	volatile bool                  stopped_;
	QMutex                         stopMutex_;

protected:
	void run();

signals:
	void sendStatus(bool isPreInHole, bool isInHole, int time_ms, double lefDis, double rightDis);  // 是否进洞
	void sendImg(const QImage&, bool is_left);
	void sendException(const char *);
};

#endif