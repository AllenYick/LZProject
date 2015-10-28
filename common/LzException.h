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
		  num:  1: 读硬件卡异常
	            2: 写硬件卡异常
				3: 相机未打开异常
				4: 相机初始化异常
				5: 相机配置异常
				6: 相机捕获异常
	*/
};
#endif