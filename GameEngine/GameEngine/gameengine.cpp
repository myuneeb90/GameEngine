#include "gameengine.h"

GameEngine::GameEngine(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	D3DWidget *widget = new D3DWidget(this);
	setCentralWidget(widget);
}

GameEngine::~GameEngine()
{

}
