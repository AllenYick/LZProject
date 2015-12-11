/****************************************************************
* @brief 
*    读取USB-4751模块数据
* @params [in]
*    端口号及对应位数
* @function
*   only read
* @author   Yike    
*        2015.06.10
*****************************************************************/

#ifndef READHARDWARE_H
#define READHARDWARE_H

#include <QtCore\QDebug>
#include "LzException.h"
#include <vector>
#include "../base/bdaqctrl.h"
#include "../base/compatibility.h"

using namespace Automation::BDaq;
using std::vector;
#define  deviceDescription  L"USB-4751,BID#0" // default

#define PORTCOUNT  1    // 每次读一个端口
#define BITCOUNT   8
typedef unsigned char byte;

class ReadHardware
{
public:
	// initialize with port-number, and it's bits to read(1~8), default 8 
	ReadHardware( int portNum, int bitCount = BITCOUNT);
	~ReadHardware();
	vector<bool> read();
	void init();
private:
	ErrorCode         ret;
	InstantDiCtrl*    instantDiCtrl;
	int               m_nPortNum;       // 端口号
	int               m_nBitCount;      // 需要读取的位数
	byte              bufferForReading; // 读取到的数据
	vector<bool>      bits;
};

#endif