#include "gameengine.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GameEngine w;
	w.show();
	return a.exec();
}
