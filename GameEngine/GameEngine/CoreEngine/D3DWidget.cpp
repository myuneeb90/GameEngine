#include "d3dwidget.h"

D3DWidget::D3DWidget(QWidget *parent) : QWidget(parent)
{
	Graphics = new GraphicsEngine();
	Graphics->GetDeviceInfo(width(), height());
	Graphics->CreateDevice(width(), height(), VSS_ENABLED, (HWND)winId(), WMT_WINDOWED);
	Graphics->CreateBuffers(width(), height());

	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);


}

D3DWidget::~D3DWidget()
{
	SAFE_DELETE(Graphics);
}

void D3DWidget::resizeEvent(QResizeEvent *evt)
{

}

void D3DWidget::paintEvent(QPaintEvent *evt)
{
	Graphics->BeginRender(0.25f, 0.25f, 0.25f, 1.0f);

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