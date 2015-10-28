#include "ReadHardwareThread.h"
#include <iostream>

ReadHardwareThread::ReadHardwareThread()
{
	stopped = false;
	bitsForReading.resize(READ_BIT_COUNT, false);
	pReadHardware = new ReadHardware(READ_PORT_NUM,READ_BIT_COUNT);
}

ReadHardwareThread::ReadHardwareThread(int portNum, int bitCount)
{
	stopped = false;
	bitsForReading.resize(bitCount);
	pReadHardware = new ReadHardware(portNum,bitCount);
}

ReadHardwareThread::~ReadHardwareThread()
{
	if( pReadHardware )
	delete pReadHardware;
}

bool ReadHardwareThread::isChanged(const vector<bool>& bits, int num)
{
	num = min(num, bits.size());
	for(int i = 0; i < num ; i++)
		if(bitsForReading[i] != bits[i])  // different
			return true;
	return false;
}


void ReadHardwareThread::init()
{
	try
	{
		pReadHardware->init();
	}
	catch(std::exception &e)
	{
		throw e;
	}
}

void ReadHardwareThread::run() 
{	
	vector<bool> bits;
	while( true )
	{
		mutex.lock();
		if(stopped)
		{
			stopped = false;
			mutex.unlock();
			break;
		}
		mutex.unlock();
		//´ÓÓ²¼þ¶ÁÈ¡
		try
		{
			bits = pReadHardware->read();
		}
		catch(std::exception &e)
		{
			qDebug() << QString(e.what());
			emit sendReadException(e.what());
			return;
		}
		
		if( isChanged(bits) )
		{
			bitsForReading = bits;
			emit sendModeChange(bits[0], bits[1], bits[2], bits[3]);  
			qDebug()<<"send, mode changed";
		}		
		QThread::msleep(50);  
	}
}

void ReadHardwareThread::stop()
{
	mutex.lock();
	stopped = true;
	mutex.unlock();
}