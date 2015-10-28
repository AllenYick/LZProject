
#include "DataModel.h"

DataModel* DataModel::m_pInstance = NULL;

bool DataModel::hasProcessed   = false;
bool DataModel::hasLeftGrabed  = false;
bool DataModel::hasRightGrabed = false;

DataModel* DataModel::getInstance()
{
	if(m_pInstance == NULL)
		m_pInstance = new DataModel();
	return m_pInstance;
}

bool DataModel::loadParameters()
{
	cv::FileStorage fs("camears.xml", cv::FileStorage::READ);
	if( !fs.isOpened() )
		return false;
	int nCameras;
	inOutTunnelThresh = double(fs["inouttunnelthresh"]);
	fs["nCameras"] >> nCameras;
	for(int i = 0; i < nCameras; i++)
	{
		char nodeName[20];
		sprintf(nodeName, "camera_%d", i+1);
		FileNode firstNode = fs[nodeName];
		string id = (string)firstNode["id"];
		cameraParas[i].id = id.c_str();
		cameraParas[i].px = (double)firstNode["px"];
		cameraParas[i].py = (double)firstNode["py"];
		cameraParas[i].fx = (double)firstNode["fx"];
		FileNode secondNode = firstNode["roi"];
		cameraParas[i].roi.x = secondNode["x"];
		cameraParas[i].roi.y = secondNode["y"];
		cameraParas[i].roi.width = secondNode["width"];
		cameraParas[i].roi.height = secondNode["height"];
	}
	return true;
}