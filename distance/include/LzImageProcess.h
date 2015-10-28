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

#ifndef	LZIMAGEPROCESS_H
#define LZIMAGEPROCESS_H

#include <opencv2\opencv.hpp>

#include "CameraConfiguration.h"
#include "LzCommon.h"

using namespace cv;
using namespace std;


class LzImage{
public:
	LzImage(const Pylon::String_t & );
	~LzImage();

	bool loadParameters();
	void init(const Mat &mat);
	void init(char* ptrMat);

	/*  获得 ROI  */
	void setROIMat();  
	/*  最大类间方差法计算阈值   */
	void ostu();

	/*  检测光斑坐标  */
	void spot_detect();

	/* save image  */
	bool saveImage(const char * szFileName);

	double process();

	void show(const string & style) const;

	Mat getRoiMat()
	{
		return mat_roi;
	}
	
private:
	Pylon::String_t     camera_id;         // 标记是哪个相机捕获的图片
	Mat         mat_src;           // 原图像      
	Mat         mat_roi;           // ROI
	Mat         mat_binary;        // 二值图
	int         segment_thresh;    // 分割阈值
	int         num_pixels;
	Point2d     spot_position;         // 斑点位置
	// description of roi
	int         roi_left;
	int         roi_top;
	int         roi_cols;
	int         roi_rows;
	double      line;           // 极线纵坐标
};	

#endif