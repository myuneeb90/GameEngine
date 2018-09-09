#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "CoreEngine/D3DWidget.h"
#include <QtWidgets/QMainWindow>

#include "ui_gameengine.h"

class GameEngine : public QMainWindow
{
	Q_OBJECT

	private:
     		Ui::GameEngineClass ui;
			WindowEngine *Window;
	public:
	  	   GameEngine(QWidget *parent = 0);
		   ~GameEngine();


};

#endif // GAMEENGINE_H
