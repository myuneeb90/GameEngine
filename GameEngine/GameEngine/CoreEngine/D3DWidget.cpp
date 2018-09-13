#include "d3dwidget.h"

D3DWidget::D3DWidget(QWidget *parent) : QWidget(parent)
{
	FirstFrame = 0;

	Debug = new DebugEngine();
	GlobalRefs::Debug = Debug;

	Graphics = new GraphicsEngine();
	GlobalRefs::Graphics = Graphics;

//	this->resize(1024, 768);
	cout<<"---- W : "<<parent->width()<<" , H : "<<parent->height()<<endl;
	any value = (uintptr_t)this->winId();
	HWND handle = (HWND)any_cast<uintptr_t>(value);

	Graphics->GetDeviceInfo(parent->width(), parent->height());
	Graphics->CreateDevice(parent->width(), parent->height(), VSS_ENABLED, (HWND)this->winId(), WMT_WINDOWED);
	Graphics->CreateBuffers(parent->width(), parent->height());

	GlobalRefs::Window->ScreenWidth = parent->width();
	GlobalRefs::Window->ScreenHeight = parent->height();


	//this->instance
	//cout<<"Wind ID : "<<(HWND)winId()<<endl;
	//cout<<"HInstance Before Assignment : "<<HInstance<<endl;
	//HInstance = GetModuleHandle(NULL);
	//cout<<"HInstance After Assignment : "<<HInstance<<endl;
	//cout<<"Parent Win ID : "<<parent->winId()<<endl;
	//cout<<"WinID : "<<this->winId()<<endl;
	//cout<<"HWND WinID : "<<handle<<endl;




	// Initialize Input
	Input = new InputEngine();
	Input->Initialize((HWND)parent->winId(), (HWND)parent->winId(), false, IS_USEKEYBOARD | IS_USEMOUSE);
	Input->AcquireAll();
	GlobalRefs::Input = Input;

	// Initialize Time
	Time = new TimeEngine();
	Time->Initialize();
	GlobalRefs::Time = Time;

	Scene = new GameScene();
	GlobalRefs::Scene = Scene;
	Scene->Awake();

	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);

	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(16);
}

D3DWidget::~D3DWidget()
{

	Scene->Destroy();
	SAFE_DELETE(Scene);

	if(Time != NULL)
	{
		SAFE_DELETE(Time);
		GlobalRefs::Time = NULL;
	}

	if(Input != NULL)
	{
		Input->Shutdown();
		SAFE_DELETE(Input);
		GlobalRefs::Input = NULL;
	}

	SAFE_DELETE(Graphics);
	SAFE_DELETE(Debug);
	GlobalRefs::Graphics = NULL;
	GlobalRefs::Scene = NULL;
	GlobalRefs::Debug = NULL;
}

void D3DWidget::resizeEvent(QResizeEvent *evt)
{
	Graphics->ReleaseBuffers();
	Graphics->SwapChain->ResizeBuffers(1, width(), height(), Graphics->SwapChainDesc.BufferDesc.Format, 0);
	Graphics->SwapChain->GetDesc(&Graphics->SwapChainDesc);
	Graphics->CreateBuffers(this->width(), this->height());

	cout<<"Resize Width : "<<this->width()<<" , Height : "<<this->height()<<endl;
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
		Input->Update();
		Time->Update(60.0f);
		Scene->Update();
	}

	Graphics->BeginRender(0.5f, 0.5f, 0.5f, 1.0f);
	Scene->Render();
	Graphics->EndRender();
}

//void D3DWidget::wheelEvent(QWheelEvent *evt)
//{
//
//}
//
//void D3DWidget::mousePressEvent(QMouseEvent *evt)
//{
//
//}
//
//void D3DWidget::mouseReleaseEvent(QMouseEvent *evt)
//{
//
//}
//
//void D3DWidget::mouseMoveEvent(QMouseEvent *evt)
//{
//
//}