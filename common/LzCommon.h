
#pragma once
#include <pylon/PylonIncludes.h>

#pragma comment (lib, "opencv_core244.lib")
#pragma comment (lib, "opencv_highgui244.lib")
#pragma comment (lib, "opencv_imgproc244.lib")

//************************************************************
// 宏定义
//************************************************************

#define uint_8 (unsigned char)
#define int_8  char
#define int_16 short
#define int_32 int
#define int_64 (long long)

//*****************************************
static const Pylon::String_t  SN_RIGHT  = "21384726";      // 右摄像头序列号
static const Pylon::String_t  SN_LEFT   = "21395135";      // 左摄像头序列号

//************** 硬件宏定义 ***************//

/*
P2口:写到A (转发来自MPC的消息)
		| D7D6:自由触发模式
			00:30Hz  01:50Hz  10:40Hz 11: 60Hz
		  D7D6:手动模式
		00:0.5m/s 01:0.75m/s  10:1.0m/s 11:1.25m/s
		| D5: 自动检测位  0:有效  1:无效
*/
#define PORT_NUM_WRITE_TO_A      2      
/*
    P5口:写到M_PC 
		|  D0D1 为进出洞状态,默认出洞
		|  00：出洞  10：预进洞  11：进洞
*/
#define PORT_NUM_WRITE_TO_MPC    5     

/*
	P1口:写到A
		| D5:自由触发模式位， 1：有效
		| D6:进出洞位        1：有效
*/
#define PORT_NUM_WRITE_IOH_TO_A  1
/*
    P4口: 读入信号
        |D0D1为工作模式，
		|D2D3为自由模式低高位(与D7D6对应)
*/
#define PORT_NUM_READ_FROM_MPC   4 

// 一个Port口包含8位
#define NUM_BITS  8  

enum WorkMode{
	WKM_AUTO     = 1,   // 工作在自动检测模式
	WKM_MANUAL   = 2,   // 手动模式
	WKM_TESTING  = 3    // 自触发模式
};

//**************** 相机宏定义 ***************//

// 采集模式
enum AcquiMode{    
	AM_SOFTWARE  = 0,   // 软件模式
	AM_HARDWARE  = 1,   // 硬件模式
	AM_CONTINUE  = 2    // 连续采集模式
};

#define NUM_CAMERAS 2

#define IS_SAVE_IMG false

//***************** 图像宏定义 ***************//
//////////////////////////////////////////////////////////////////////////
//  ------------------------宏定义 ---------------------------
#define FRAME_COLS    (ROI_WIDTH)      // default 1280
#define FRAME_ROWS    (ROI_HEIGHT)     // default  1024
#define FRAME_SIZE    (FRAME_COLS*FRAME_ROWS)
#define PIXELTHRESH   (1000)

#define BSL (0.5)  
//////////////////////////////////////////////////////////////////////////
// -----------------左相机参数-----------------------
//const QString  SN_LEFT   = "21395135";      // 左摄像头序列号
// 定义左图像ROI
#define LEFT_ROI_LEFT     (480)    // 
#define LEFT_ROI_COLS     (FRAME_COLS-LEFT_ROI_LEFT)   // 宽
#define LEFT_ROI_TOP      (500)   // 极线：573
#define LEFT_ROI_ROWS     (100)    // 
#define LEFT_ROI_SIZE     (LEFT_ROI_COLS*LEFT_ROI_ROWS)
#define LEFT_LINE         (573)
// 定义左相机内参

//fc = [ 956.99555   960.22100 ]
//cc = [ 658.39293   546.10319 ]
#define   LEFT_PX        (658.393)       // 主点坐标，x
#define   LEFT_PY        (546.103)        // 主点坐标，y
#define   LEFT_FX        (956.996)       // 焦距与x轴物理尺寸比值

// -----------------右相机参数-----------------------
//const QString  SN_RIGHT = "21384726";      // 右摄像头序列号
// 定义右图像ROI
#define RIGHT_ROI_LEFT     (0)    // 
#define RIGHT_ROI_COLS     (800)   // 宽
#define RIGHT_ROI_TOP      (500)    // 极线:534
#define RIGHT_ROI_ROWS     (100)    // 
#define RIGHT_ROI_SIZE     (LEFT_ROI_COLS*LEFT_ROI_ROWS)
#define RIGHT_LINE         (538)

// 定义右相机内参
//{944.067,0,624.843}
//{0,947.074,584.412}
//{0,0,1}

//fc = [ 966.81486   968.77085 ]
//cc = [ 635.39424   523.60966 ]
#define   RIGHT_PX       (635.394)        // 主点坐标，x
#define   RIGHT_PY       (523.60967)      // 主点坐标，y
#define   RIGHT_FX       (966.815)        // x轴物理尺寸比值

//***************** 进出洞管理对象宏定义 ***************//
//
#define  INOUTHOLE_THRESH    6.0   // 片刻进出洞阈值

