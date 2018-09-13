#ifndef WINDOW_ENGINE_H
#define WINDOW_ENGINE_H

#include <QtWidgets/qstatusbar.h>

class WindowEngine
{
	public:
			QStatusBar *StatusBar;
			int ScreenWidth;
			int ScreenHeight;
	public:
			WindowEngine();
			virtual ~WindowEngine();

};

#endif