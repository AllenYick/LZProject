/****************************************************************
**lz_mainwindow.h
* @brief 
*   main-window
* @author   Yike    
*          2015.06.10
*****************************************************************/
#ifndef LZ_MAINWINDOW_H
#define LZ_MAINWINDOW_H

#include <Windows.h>
#include <QtGui/QMainWindow>
#include <QMessageBox>
#include <QTime>

#include "LzCommon.h"
#include "ui_lz_mainwindow.h"
#include "AutoDetectThread.h"
#include "ReadHardwareThread.h"
#include "ReadHardware.h"
#include "WriteHardware.h"
#include "TriangleDistance.h"
#include "DataModel.h"
// for test


class LZ_MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	LZ_MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~LZ_MainWindow();
	QString  strategyToStr();
	void     initHardware();
	QImage   MatToQImage(const Mat& mat);

public slots:
	void receiveStatus(bool isPreInHole, bool isInHole, int time_ms, double leftDis, double rightDis);
	void receiveException(const char *);
	void receiveImg(const QImage &, bool); // 0:left, 1:right
	void receiveModeChange(bool b0, bool b1, bool b2, bool b3);

	
	/*@brief  for button */
	void onSetInHoleButton();
	void onSetOutHoleButton();
	/*@brief  for action */
	void onActionAbout();
	void onActionExit();
	/* @brief for initialize  */
	void initCameras();
	
private:
	Ui::LZ_MainWindowClass ui;
private:
	bool                    bIsInitHardware_;            // Ӳ���Ƿ��ʼ���ɹ�
	bool                    bIsReadFromMPC_;            // ��ȡM_PC��Ϣ�Ƿ�ɹ�
	bool                    bIsInitCamera_;              // ��ʼ������Ƿ�ɹ�
	AutoDetectThread*       pAutoDetectThread_;             // �Զ�������
	ReadHardwareThread*     pReadHardWareThread_;
	WriteHardware*          pWriteToMPC_IOH_;                 // д��������Ϣ��M_PC
	WriteHardware*          pWriteToA_IOH_;                   // д��������Ϣ��A
	WriteHardware*          pWriteToA_FromMPC_;              // д����M_PC����Ϣ��A
	ReadHardware*           pReadFromMPC_;                   // ��M_PC��ȡ��Ϣ
	vector<bool>            vBitsWriteToMPC_IOH_;
	vector<bool>            vBitsWriteToA_IOH_;
	vector<bool>            vBitsReadFromMPC_;
	vector<bool>            vBitsWriteToA_FromMPC_;
	WorkMode                workMode_;
	bool                    bIsPreInHole_;     // �Ƿ�Ԥ����
	bool                    bIsInHole_;        // �Ƿ����
	bool					bIsPressInholeButton_;     // �Ƿ��˽�����ť
	bool                    bIsPressOutholeButton_;    // �Ƿ��˳�����ť
};

#endif 
