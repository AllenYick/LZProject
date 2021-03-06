#include "../include/TriangleDistance.h"
#include "DataModel.h"

TriangleDistance::TriangleDistance(const Pylon::String_t& _id)
{
	camera_id = _id;
	DataModel* m = DataModel::getInstance();
	size_t i = 0;
	while(i < NUM_CAMERAS && m->cameraParas[i].id != _id)
		i++;
	main_point.x = m->cameraParas[i].px;
	main_point.y = m->cameraParas[i].py;
	fx = m->cameraParas[i].fx;
	baseLine = m->cameraParas[i].baseline;
	roi_left = m->cameraParas[i].roi.x;
	angle_of_tan  = m->cameraParas[i].angleTan;
	m = NULL;
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
	if(spotx < 0.0)
		distance = -1.0;
	else
		distance =  baseLine * fx /(abs(spotx+roi_left-main_point.x)+fx*angle_of_tan);
	return distance;
}