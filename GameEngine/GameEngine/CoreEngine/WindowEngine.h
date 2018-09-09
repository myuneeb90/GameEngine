#ifndef WINDOW_ENGINE_H
#define WINDOW_ENGINE_H

#include <QtWidgets/qstatusbar.h>

class WindowEngine
{
	public:
			QStatusBar *StatusBar;
	public:
			WindowEngine();
			virtual ~WindowEngine();

};

#endif