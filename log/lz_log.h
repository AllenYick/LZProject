#ifndef LZ_LOG_H
#define LZ_LOG_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
 * 兰州项目日志类声明，记录各种日志信息
 */
class LzLog
{
public:
	enum LogType{
		Information = 0, 		// 
		Error = 1, 		// 文件传输，主要负责记录Backup的情况
	};

	LzLog(LogType type);
	
	~LzLog();
	
    /**
     * 外部接口，是否正在写入文件，文件正打开
     */
    bool isLogging();

	/**
     * 文件名（含路径)
     */
	void setFilename(string newfilename);
	
	/**
	 * @return 0 open已有文件成功
	 * 	1 没有已有文件，但创建成功
	 *	2 没有已有文件，且创建文件失败
	 */
	int open();

	void close();

	/**
	 * 日志记录
	 * @param msg a string to log
	 */
	void log(string msg);

private:

	// 文件名（含路径)
	string filename;
	
	// 文件类型
	LogType fileType;
	
	// 文件是否打开
	bool isopen;

    /**
     * 输出流
     */
    ofstream out;
};

#endif // LZ_LOGGER_H