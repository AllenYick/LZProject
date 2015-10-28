#include "acqutest.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AcquTest w;
	w.show();
	return a.exec();
}
