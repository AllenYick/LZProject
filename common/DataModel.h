
#ifndef DATAMODEL_H_
#define DATAMODEL_H_

#include <QtGui>
#include <map>
#include <vector>

#include <opencv2\opencv.hpp>

#include "LzCommon.h"

using namespace cv;

struct CameraPara 
{
	Pylon::String_t id;
	double px;
	double py;
	double fx;
	double baseline;
	cv::Rect roi;
	int line_height;   // 
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
	bool loadParameters();
	double inOutTunnelThresh;

private:
	// µ¥ÀýÄ£Ê½
	DataModel(){
		mats.clear();
		mats.resize(NUM_CAMERAS);
		qImages.clear();
		qImages.resize(NUM_CAMERAS);
		loadParameters();
	};
	static DataModel* m_pInstance;
};

#endif
