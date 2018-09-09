#include "gameengine.h"

GameEngine::GameEngine(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	Window = new WindowEngine();
	GlobalRefs::Window = Window;

	D3DWidget *widget = new D3DWidget(this);
	setCentralWidget(widget);

	//QStatusBar *statusBar = GameEngine::findChild<QStatusBar*>("statusBar");
	Window->StatusBar = GameEngine::findChild<QStatusBar*>("statusBar");
	Window->StatusBar->showMessage("Ready", 0);
}

GameEngine::~GameEngine()
{
	SAFE_DELETE(Window);
	GlobalRefs::Window = NULL;
}
