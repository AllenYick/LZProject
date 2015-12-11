#include "lz_mainwindow.h"
#include <QtGui/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
	QApplication a(argc, argv);
	QApplication::setStyle("cleanlooks"); 
	LZ_MainWindow w;
	w.setWindowOpacity(1);  
	//w.setWindowFlags(Qt::FramelessWindowHint);  
	w.setGeometry(QRect(200, 200, 982-420, 677));
	w.show();
	return a.exec();
}
