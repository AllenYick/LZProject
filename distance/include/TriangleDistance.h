/****************************************************************
*TriangleDistance.h
* @brief 
*   Image preprocessing , blob detecting and distance computing .
*
* @params
*    image and the id of camera which grab image.

* @author   Yike    
*          2015.06.10
*****************************************************************/

#ifndef	TRIANGLEDISTANCE_H
#define TRIANGLEDISTANCE_H

#include <opencv2\opencv.hpp>
#include <QtCore\QString>

#include "CameraConfiguration.h"
#include "LzCommon.h"
#include "LzImageProcess.h"

using namespace cv;
using namespace std;

class LzImage;
class TriangleDistance
{
public: 
	TriangleDistance(const Pylon::String_t& _id);

	~TriangleDistance();
	/* two ways to init   */
	void init(const Mat &img);
	void init(char * ptrImg);
	double compute();           // 调用图像处理函数计算斑点，返回距离
	/* object to process image */
	LzImage *img_for_process;

private:
	Pylon::String_t    camera_id;
	cv::Point2d        main_point;       // 主点坐标
	double         fx;
	double         angle_of_tan;     // 倾斜角，默认0.0
	double         distance;	     // 三角距离
	int            roi_left;
	double         baseLine;        // 基线长
};

#endif