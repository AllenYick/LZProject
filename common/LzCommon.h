
#pragma once
#include <pylon/PylonIncludes.h>

#pragma comment (lib, "opencv_core244.lib")
#pragma comment (lib, "opencv_highgui244.lib")
#pragma comment (lib, "opencv_imgproc244.lib")

//************************************************************
// �궨��
//************************************************************

#define uint_8 (unsigned char)
#define int_8  char
#define int_16 short
#define int_32 int

//*****************************************
static const Pylon::String_t  SN_RIGHT  = "21384726";      // ������ͷ���к�
static const Pylon::String_t  SN_LEFT   = "21395135";      // ������ͷ���к�

//************** Ӳ���궨�� ***************//

/*
P2��:д��A (ת������MPC����Ϣ)
		| D7D6:���ɴ���ģʽ
			00:30Hz  01:50Hz  10:40Hz 11: 60Hz
		  D7D6:�ֶ�ģʽ
		00:0.5m/s 01:0.75m/s  10:1.0m/s 11:1.25m/s
		| D5: �Զ����λ  0:��Ч  1:��Ч
*/
#define PORT_NUM_WRITE_TO_A      2      
/*
    P5��:д��M_PC 
		|  D0D1 Ϊ������״̬,Ĭ�ϳ���
		|  00������  10��Ԥ����  11������
*/
#define PORT_NUM_WRITE_TO_MPC    5     

/*
	P1��:д��A
		| D5:���ɴ���ģʽλ�� 1����Ч
		| D6:������λ        1����Ч
*/
#define PORT_NUM_WRITE_IOH_TO_A  1
/*
    P4��: �����ź�
        |D0D1Ϊ����ģʽ��
		|D2D3Ϊ����ģʽ�͸�λ(��D7D6��Ӧ)
*/
#define PORT_NUM_READ_FROM_MPC   4 

// һ��Port�ڰ���8λ
#define NUM_BITS  8  

enum WorkMode{
	WKM_AUTO     = 1,   // �������Զ����ģʽ
	WKM_MANUAL   = 2,   // �ֶ�ģʽ
	WKM_TESTING  = 3    // �Դ���ģʽ
};

//**************** ����궨�� ***************//

// �ɼ�ģʽ
enum AcquiMode{    
	AM_SOFTWARE  = 0,   // ����ģʽ
	AM_HARDWARE  = 1,   // Ӳ��ģʽ
	AM_CONTINUE  = 2    // �����ɼ�ģʽ
};

#define NUM_CAMERAS 2

#define IS_SAVE_IMG false

//***************** ͼ��궨�� ***************//
//////////////////////////////////////////////////////////////////////////
//  ------------------------�궨�� ---------------------------
#define FRAME_COLS    (ROI_WIDTH)      // default 1280
#define FRAME_ROWS    (ROI_HEIGHT)     // default  1024
#define FRAME_SIZE    (FRAME_COLS*FRAME_ROWS)
#define PIXELTHRESH   (1000)

#define BSL (0.5)  
//////////////////////////////////////////////////////////////////////////
// -----------------���������-----------------------
//const QString  SN_LEFT   = "21395135";      // ������ͷ���к�
// ������ͼ��ROI
#define LEFT_ROI_LEFT     (480)    // 
#define LEFT_ROI_COLS     (FRAME_COLS-LEFT_ROI_LEFT)   // ��
#define LEFT_ROI_TOP      (500)   // ���ߣ�573
#define LEFT_ROI_ROWS     (100)    // 
#define LEFT_ROI_SIZE     (LEFT_ROI_COLS*LEFT_ROI_ROWS)
#define LEFT_LINE         (573)
// ����������ڲ�

//fc = [ 956.99555   960.22100 ]
//cc = [ 658.39293   546.10319 ]
#define   LEFT_PX        (658.393)       // �������꣬x
#define   LEFT_PY        (546.103)        // �������꣬y
#define   LEFT_FX        (956.996)       // ������x�������ߴ��ֵ

// -----------------���������-----------------------
//const QString  SN_RIGHT = "21384726";      // ������ͷ���к�
// ������ͼ��ROI
#define RIGHT_ROI_LEFT     (0)    // 
#define RIGHT_ROI_COLS     (800)   // ��
#define RIGHT_ROI_TOP      (500)    // ����:534
#define RIGHT_ROI_ROWS     (100)    // 
#define RIGHT_ROI_SIZE     (LEFT_ROI_COLS*LEFT_ROI_ROWS)
#define RIGHT_LINE         (538)

// ����������ڲ�
//{944.067,0,624.843}
//{0,947.074,584.412}
//{0,0,1}

//fc = [ 966.81486   968.77085 ]
//cc = [ 635.39424   523.60966 ]
#define   RIGHT_PX       (635.394)        // �������꣬x
#define   RIGHT_PY       (523.60967)      // �������꣬y
#define   RIGHT_FX       (966.815)        // x�������ߴ��ֵ

//***************** ��������������궨�� ***************//
//
#define  INOUTHOLE_THRESH    6.0   // Ƭ�̽�������ֵ
