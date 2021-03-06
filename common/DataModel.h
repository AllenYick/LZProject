
#ifndef DATAMODEL_H_
#define DATAMODEL_H_

#include <QtGui>
#include <map>
#include <vector>

#include <opencv2\opencv.hpp>

#include "LzCommon.h"

using namespace cv;

// 存储相机和图像处理参数的结构体
struct CameraPara 
{
	// 相机
	Pylon::String_t id;  // 唯一的ID
	double px;
	double py;
	double fx;
	double baseline;
	double angleTan; 
	// 图像
	cv::Rect roi;
	int line_height;   // 极线的y坐标
};

class DataModel
{
public:
	std::vector<QImage>    qImages;
	std::map<Pylon::String_t, int> id_to_index;
	std::vector<cv::Mat>   mats;
	
	static DataModel *getInstance();
	static bool hasLeftGrabed;
	static bool hasRightGrabed;
	static bool hasProcessed;

	// 
	CameraPara cameraParas[NUM_CAMERAS];
	bool loadParameters(string fileName);
	double inOutTunnelThresh;

private:
	// 单例模式
	DataModel(){
		mats.clear();
		mats.resize(NUM_CAMERAS);
		qImages.clear();
		qImages.resize(NUM_CAMERAS);
	};
	static DataModel* m_pInstance;
};

#endif
