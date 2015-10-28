#include "../include/LzImageProcess.h"

LzImage::LzImage(const Pylon::String_t & _id)
{
	camera_id = _id;
	if(camera_id == SN_LEFT)
	{
		roi_left = LEFT_ROI_LEFT;
		roi_cols = LEFT_ROI_COLS;
		roi_top = LEFT_ROI_TOP;
		roi_rows = LEFT_ROI_ROWS;
		line = LEFT_LINE;
	}
	else
	{
		roi_left = RIGHT_ROI_LEFT;
		roi_cols = RIGHT_ROI_COLS;
		roi_top = RIGHT_ROI_TOP;
		roi_rows = RIGHT_ROI_ROWS;
		line = RIGHT_LINE;
	}
}

void LzImage::init(const Mat &img)
{
	img.copyTo(mat_src);
	if( mat_src.channels() == 3)   // 转化为灰度图像
		cvtColor(mat_src, mat_src, CV_RGB2GRAY);

	spot_position.x = spot_position.y = -1;  // 斑点坐标默认取(-1,-1)
	segment_thresh = 0;
}

void LzImage::init(char *ptrGrabResultBuffer)
{
	if(!mat_src.data)
		mat_src.create(FRAME_ROWS, FRAME_COLS, CV_8UC1);
	memcpy(mat_src.data, ptrGrabResultBuffer, FRAME_SIZE);
	spot_position.x = spot_position.y = -1;
	segment_thresh = 0;
}

void LzImage::show(const string& style) const
{
	if( style == "B" && mat_binary.data )
	{
		Mat temp;
		mat_binary.copyTo(temp);
		std::stringstream buf;
		buf << "Px: " << spot_position.x << " Py: " << spot_position.y << " Thresh: " << segment_thresh << " COUNT: " << num_pixels ;
		string num = buf.str();
		putText(temp, num, Point(15,20),FONT_HERSHEY_SIMPLEX,0.8,Scalar(255,255,255),0.5);
		rectangle( temp, Rect((int)spot_position.x-10,(int)spot_position.y-10,20,20), Scalar(255,255,255), 2);
		imshow(string(camera_id) + " ROI", temp);
	}
	else if( style == "R")
	{
		Mat temp;
		mat_roi.copyTo(temp);
		std::stringstream buf;
		buf << "Px: " << spot_position.x << " Py: " << spot_position.y << " Thresh: " << segment_thresh << " COUNT: " << num_pixels ;
		string num = buf.str();
		putText(temp, num, Point(15,20),FONT_HERSHEY_SIMPLEX,0.8,Scalar(255,255,255),0.5);
		rectangle( temp, Rect((int)spot_position.x-10,(int)spot_position.y-10,20,20), Scalar(255,255,255), 2);
		imshow(string(camera_id) + " ROI", temp);
	}
	else
	{
		Mat temp;
		pyrDown(mat_src, temp, Size( mat_src.cols/2, mat_src.rows/2 ));
		std::stringstream buf;
		buf << "Px: " << spot_position.x << " Py: " << spot_position.y << "Thresh: " << segment_thresh;
		string num = buf.str();
		putText(temp, num, Point(20,30),FONT_HERSHEY_SIMPLEX,1,Scalar(255,255,255), 0.5);
		rectangle( temp, Rect((int)spot_position.x-10,(int)spot_position.y-10,20,20), Scalar(255,255,255), 2);
		imshow(string(camera_id) + " SRC", temp);
	}

	char c = waitKey(10);
	if( c == 27 )
	{
		exit(-1);
		return;
	}
}

LzImage::~LzImage()
{
	mat_src.release();
	mat_roi.release();
	mat_binary.release();
}

/*  获得ROI图像  */
void LzImage::setROIMat()
{ 
	Mat subView = mat_src( Range(roi_top, roi_top+roi_rows), 
		Range(roi_left, roi_left+roi_cols) );
	subView.copyTo(mat_roi);
	return;
}

/*  OSTU 最大类间方差法计算阈值，用于分割图像*/
void  LzImage::ostu() 
{
	int threshold  = 0;
	int hist[256] = {0};
	uchar *p = (uchar *)mat_roi.data;
	for(int i = 0; i < roi_rows; i++)
	{
		for(int j = 0; j < roi_cols; j++)
		{
			hist[*p++]++;
			//histogram[img.ptr<uchar>(i)[j]]++;   //指针访问方式
		}
	}
	// normalize histogram
	double histogram[256] = {0};        // 初始化直方图为零
	for(int i = 0; i < 256; i++)
	{
		histogram[i]  = double(hist[i])/ double(roi_rows*roi_cols);
	}
	// 迭代寻找最优值
	double maxval = 0;
	for(int i = 0; i < 256; ++i)    // 从0到256迭代
	{
		double omiga_0 = 0.0;
		for(int j = 0; j < i; ++j)
		{
			omiga_0  += histogram[j];
		}
		double omiga_1 = 1.0 - omiga_0;

		double mu_0 = 0.0;
		for(int j = 0; j < i; ++j)
		{
			mu_0  += j*histogram[j];
		}
		mu_0 /= omiga_0;

		double mu_1 = 0.0;
		for(int j = i; j < 256; ++j)
		{
			mu_1 += j*histogram[j];
		}
		mu_1 /= omiga_1;

		double var_0 = 0.0;   // 方差
		for(int j = 0; j < i; j++)
		{
			var_0 += (j-mu_0)*(j-mu_0)*histogram[j];
		}
		var_0 /= omiga_0;

		double var_1 = 0.0;  // 方差
		for(int j = i; j < 256; ++j)
		{
			var_1 += (j-mu_1)*(j-mu_1)*histogram[j];
		}
		var_1 /= omiga_1;

		double val = omiga_0 * omiga_0 * ( mu_1 - mu_0 ) * ( mu_1 - mu_0 )
			/( omiga_0 * var_0 + omiga_1 * var_1 );
		if( val > maxval )   // 返回是maxval最大的i值
		{
			maxval     =  val;
			threshold  =  i;
		}
	}
	 segment_thresh = (threshold== 0 ? 255 : threshold);
	 return;
}

void LzImage::spot_detect()   // 检测图像的光斑点
{
	int sumX   =  0;             // x分量的和
	int sumY   =  0;             // y分量的和
	num_pixels   =  0;             // 不为0的坐标个数
	
	//double t = double(getTickCount());
	if( mat_binary.isContinuous())
	{
		uchar *p =  mat_binary.data;
		for(int i = 0; i < roi_rows; i++)
		{
			for(int j = 0; j < roi_cols; j++)
			{
				if(*p != 0)
				{
					// 注意这里是图像坐标系
					sumX += j;   sumY += i;   num_pixels++;		
				}
				p++;
			}
		}
	}
	else
	{
		//for(int i = 0; i < roi_rows; i++)
		//{
		//	for(int j = 0; j < roi_cols; j++)
		//	{
		//		if(m_IBinaryImg.at<i>[j])
		//			// 注意这里是图像坐标系
		//			sumX += j;   sumY += i;   m_nCount++;		
		//		p++;
		//	}
		//}
	}
	
	if(num_pixels != 0 && num_pixels < PIXELTHRESH )  // length 不为零且斑点面积小于阈值
	{ 
		spot_position.x = double(sumX) / num_pixels;
		spot_position.y = double(sumY) / num_pixels;		
	}
	else   // 未找到斑点
	{
		spot_position.x = spot_position.y = -1;        
	}
	
	if( fabs(spot_position.y + roi_top - line) > 100 ) // 斑点不在极线附近
	{ 
		spot_position.y = -1;
		spot_position.x = -1;
	}
	return;		
}

bool LzImage::saveImage(const char * fileName)
{
	cv::imwrite(fileName, mat_src);
	return true;
}

double LzImage::process()
{
	setROIMat();
	ostu();
	threshold( mat_roi, mat_binary, segment_thresh-1, 255, CV_THRESH_BINARY );    // 阈值分割图像
	medianBlur(mat_binary, mat_binary, 3);
	spot_detect();
	return spot_position.x;
}




