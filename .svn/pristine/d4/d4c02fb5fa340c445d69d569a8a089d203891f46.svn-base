#include "../include/TriangleDistance.h"

TriangleDistance::TriangleDistance(const Pylon::String_t& _id)
{
	camera_id = _id;
	if( _id == SN_LEFT)
	{
		main_point.x = LEFT_PX;
		main_point.y = LEFT_PY;
		fx = LEFT_FX;
		roi_left = LEFT_ROI_LEFT;
		angle_of_tan  = 0;
	}
	else
	{
		main_point.x = RIGHT_PX;
		main_point.y = RIGHT_PX;
		fx = RIGHT_FX;
		roi_left = RIGHT_ROI_LEFT;
		angle_of_tan  = 0;
	}	
	img_for_process = new LzImage(_id);
}

void TriangleDistance::init(char* ptrImg)
{
	img_for_process->init(ptrImg);
}

void TriangleDistance::init(const Mat &img)
{
	img_for_process->init(img);
}

TriangleDistance::~TriangleDistance()
{
	delete img_for_process;
}

double TriangleDistance::compute()
{
	double spotx = img_for_process->process();
	if(spotx < 0)
		distance = -1;
	else
		distance =  BSL * fx /(abs(spotx+roi_left-main_point.x)+fx*angle_of_tan);
	return distance;
}