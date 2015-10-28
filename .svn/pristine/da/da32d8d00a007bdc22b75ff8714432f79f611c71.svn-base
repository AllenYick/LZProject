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
	bool                    bIsInitHardware_;            // 硬件是否初始化成功
	bool                    bIsReadFromMPC_;            // 读取M_PC消息是否成功
	bool                    bIsInitCamera_;              // 初始化相机是否成功
	AutoDetectThread*       pAutoDetectThread_;             // 自动检测进程
	ReadHardwareThread*     pReadHardWareThread_;
	WriteHardware*          pWriteToMPC_IOH_;                 // 写进出洞信息到M_PC
	WriteHardware*          pWriteToA_IOH_;                   // 写进出洞消息到A
	WriteHardware*          pWriteToA_FromMPC_;              // 写来自M_PC的消息到A
	ReadHardware*           pReadFromMPC_;                   // 从M_PC读取消息
	vector<bool>            vBitsWriteToMPC_IOH_;
	vector<bool>            vBitsWriteToA_IOH_;
	vector<bool>            vBitsReadFromMPC_;
	vector<bool>            vBitsWriteToA_FromMPC_;
	WorkMode                workMode_;
	bool                    bIsPreInHole_;     // 是否预进洞
	bool                    bIsInHole_;        // 是否进洞
	bool					bIsPressInholeButton_;     // 是否按了进洞按钮
	bool                    bIsPressOutholeButton_;    // 是否按了出洞按钮
};

#endif 
