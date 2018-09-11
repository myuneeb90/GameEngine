#include "d3dwidget.h"

D3DWidget::D3DWidget(QWidget *parent) : QWidget(parent)
{
	FirstFrame = 0;

	Debug = new DebugEngine();
	GlobalRefs::Debug = Debug;

	Graphics = new GraphicsEngine();
	GlobalRefs::Graphics = Graphics;
	Graphics->GetDeviceInfo(width(), height());
	Graphics->CreateDevice(width(), height(), VSS_ENABLED, (HWND)winId(), WMT_WINDOWED);
	Graphics->CreateBuffers(width(), height());

	Scene = new GameScene();
	GlobalRefs::Scene = Scene;
	Scene->Awake();

	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);
}

D3DWidget::~D3DWidget()
{
	Scene->Destroy();
	SAFE_DELETE(Scene);
	SAFE_DELETE(Graphics);
	SAFE_DELETE(Debug);
	GlobalRefs::Graphics = NULL;
	GlobalRefs::Scene = NULL;
	GlobalRefs::Debug = NULL;
}

void D3DWidget::resizeEvent(QResizeEvent *evt)
{

}

void D3DWidget::paintEvent(QPaintEvent *evt)
{
	if(FirstFrame == 0)
	{
		Scene->Start();
		FirstFrame = 1;
	}

	if(FirstFrame == 1)
	{
		Scene->Update();
	}

	Graphics->BeginRender(0.25f, 0.25f, 0.25f, 1.0f);
	Scene->Render();
	Graphics->EndRender();
}

void D3DWidget::wheelEvent(QWheelEvent *evt)
{

}

void D3DWidget::mousePressEvent(QMouseEvent *evt)
{

}

void D3DWidget::mouseReleaseEvent(QMouseEvent *evt)
{

}

void D3DWidget::mouseMoveEvent(QMouseEvent *evt)
{

}