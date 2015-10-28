/****************************************************************
*	LzCamera.h
* @brief 
*	my own exception class
* @params
*   id(int) and description(char*)
* @author   Yike    
*          2015.06.10
*****************************************************************/
#ifndef LZEXCEPTION_H
#define LZEXCEPTION_H

#include <exception>

class LzException : public std::exception
{
public:
	LzException(int _num, const char * msg) :num(_num), exception(msg){};
	int num;
	/*@param
		  num:  1: ��Ӳ�����쳣
	            2: дӲ�����쳣
				3: ���δ���쳣
				4: �����ʼ���쳣
				5: ��������쳣
				6: ��������쳣
	*/
};
#endif