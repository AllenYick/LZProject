/****************************************************************
* @brief 
*    д�����ݵ�USB-4751ģ��
* @params [in]
*    �˿ںż���Ӧλ��
* @function
*   write and read
* @author   Yike    
*          2015.06.10
*****************************************************************/

#ifndef WRITEHARDWARE_H
#define WRITEHARDWARE_H

#include <QtCore\QDebug>
#include <vector>
// base h file
#include "../base/bdaqctrl.h"
#include "../base/compatibility.h"
#include "LzException.h"

#define  deviceDescription  L"USB-4751,BID#0"

#define PORTCOUNT  1    // ÿ��дһ���˿�
#define BITCOUNT   8

using namespace Automation::BDaq;
using std::vector;

typedef unsigned char byte;

class WriteHardware
{
public:
	/* initialize with port-number, and it's bits to write(1~8), default 8  */
	WriteHardware(int portNum, int bitCount = BITCOUNT);
	~WriteHardware();

	void init();
	void write(const vector<bool>&);
	void write(byte byteForWriting);
	vector<bool> read();
	
private:
	ErrorCode         ret;
	InstantDoCtrl *   instantDoCtrl;
	int               m_nPortNum;
	int               m_nBitCount;
};

#endif
