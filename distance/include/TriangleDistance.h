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
	double compute();           // ����ͼ������������ߵ㣬���ؾ���
	/* object to process image */
	LzImage *img_for_process;

private:
	Pylon::String_t    camera_id;
	cv::Point2d        main_point;       // ��������
	double         fx;
	double         angle_of_tan;     // ��б�ǣ�Ĭ��0.0
	double         distance;	     // ���Ǿ���
	int            roi_left;
};

#endif