/*/////////////////////////////////////////////////////////
*
*	ImgFromFile.h
*	нд╪Ч	
*
*//////////////////////////////////////////////////////////

#ifndef IMGFROMFILE_H
#define IMGFROMFILE_H

#include <opencv2\opencv.hpp>
#include <direct.h>
#include <vector>
#include <io.h>
#include <string>
#include <stdlib.h>
#include <cv.h>
#include <highgui.h>

using std::string;
using cv::Mat;
using std::vector;

const char FILE_TYPE[] = "%d.png";
#define IMG_FILE_BEGIN  1

class ImgFile
{
public:
	ImgFile();
	bool setInitDir(const char* dir);
	bool readNextImg();
	Mat getImg()
	{
		return m_IImg;
	}
private:
	int      m_nFileCount;
	int      m_nTotalFileCount;
	char   m_szFileFormat[_MAX_PATH];
	Mat m_IImg;
};

#endif