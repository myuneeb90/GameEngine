#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "CoreEngine/D3DWidget.h"
#include <QtWidgets/QMainWindow>
#include "ui_gameengine.h"

class GameEngine : public QMainWindow
{
	Q_OBJECT

public:
	GameEngine(QWidget *parent = 0);
	~GameEngine();

private:
	Ui::GameEngineClass ui;
};

#endif // GAMEENGINE_H
