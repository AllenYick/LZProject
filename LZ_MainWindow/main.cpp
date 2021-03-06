#include <QtGui/QApplication>
#include <QTextCodec>
#include "lz_mainwindow.h"
#include "DataModel.h"


int main(int argc, char *argv[])
{
	// 加载相机参数
	DataModel* m = DataModel::getInstance();
	if(!m->loadParameters("cameras_info.xml"))
	{
		MessageBox(NULL, TEXT("未缺少xml文件,无法进行自动检测!"), TEXT("错误"), MB_OK);
	}
	m = NULL;
	QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
	QApplication a(argc, argv);
	QApplication::setStyle("cleanlooks"); 
	LZ_MainWindow w;
	w.setWindowOpacity(1);  
	//w.setWindowFlags(Qt::FramelessWindowHint); 
	w.show();
	return a.exec();
}
