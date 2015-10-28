#include "ImgFromeFile.h"

ImgFile::ImgFile()
{
	m_nFileCount = IMG_FILE_BEGIN;
	m_nTotalFileCount = 0;
	m_IImg = 0;
}
  
bool ImgFile::setInitDir(const char * dir)
{
	//if(_chdir("D:") != 0)   //  if exist this dir
	//	return false;
		
	char filename[_MAX_PATH] = {'\0'};
	strcpy(filename, dir);
	strcat(filename, "*.png");
	long longf;
	_finddata_t file;
	if((longf = _findfirst(filename, &file) )== -1L)
		return false;
	while( _findnext( longf, &file ) == 0)
	{
		if( strcmp(file.name,  "..") == 0 )
			continue;
		m_nTotalFileCount++;
	}
	_findclose(longf);
	sprintf(m_szFileFormat, "%s%s", dir, FILE_TYPE);
	return true;
}

bool ImgFile::readNextImg()
{
	if( m_nFileCount <= m_nTotalFileCount )
	{
		char fileName[_MAX_PATH]={'\0'};
		sprintf(fileName, m_szFileFormat, m_nFileCount);
		if( !m_IImg.empty() )
			m_IImg.release();
		m_IImg = cv::imread(fileName);
		if( !m_IImg.data )
			return false;
		std::cout << fileName << std::endl;
		m_nFileCount++;
		return true;
	}
	return false;
}