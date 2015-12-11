/************************************************************************
*ReadHardwareThread.h
* @brief 
*   thread for read bits from USB-4751
* @params
*    the port's number and bits to read
* @author   Yike    
*          2015.06.10
*****************************************************************/
#ifndef READHARDWARETHREAD_H
#define READHARDWARETHREAD_H

#include <QtCore\QThread>
#include <QtCore\QDebug>
#include <QtCore\QMutex>

#include "ReadHardware.h"

#define  READ_PORT_NUM    0
#define  READ_BIT_COUNT   8

class ReadHardwareThread : public QThread
{
	Q_OBJECT
public:
	ReadHardwareThread();
	ReadHardwareThread(int portNum, int bitCount = READ_BIT_COUNT);
	~ReadHardwareThread();
	void init();
	bool isChanged(const vector<bool>&, int num = READ_BIT_COUNT);
	void stop();
protected:
	void run();
private:
	vector<bool>     bitsForReading;
	ReadHardware*    pReadHardware;     // pointer of readHardware
	QMutex           mutex;
	volatile bool    stopped;
signals:
	void sendModeChange(bool b0, bool b1, bool b2, bool b3);
	void sendReadException(const char *);
};

#endif