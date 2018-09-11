#ifndef D3D_WIDGET_H
#define D3D_WIDGET_H

#include "CoreEngine/AppMain.h"
#include <qwidget.h>
#include <QtWidgets/QApplication>

class D3DWidget : public QWidget
{
	Q_OBJECT
	Q_DISABLE_COPY(D3DWidget)

	private:
			GraphicsEngine *Graphics;
			DebugEngine *Debug;
			BaseScene *Scene;
			int FirstFrame;
	protected:
			  virtual void resizeEvent(QResizeEvent *evt);
			  virtual void paintEvent(QPaintEvent *evt);
			  virtual void wheelEvent(QWheelEvent *evt);
			  virtual void mousePressEvent(QMouseEvent *evt);
			  virtual void mouseReleaseEvent(QMouseEvent *evt);
			  virtual void mouseMoveEvent(QMouseEvent *evt);
	public:
			D3DWidget(QWidget *parent = NULL);
			virtual ~D3DWidget();
			virtual QPaintEngine* paintEngine() const { return NULL; }
			
};

#endif