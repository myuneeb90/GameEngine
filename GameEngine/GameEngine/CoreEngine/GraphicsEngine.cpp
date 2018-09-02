#include "CoreEngine/AppMain.h"

GraphicsEngine::GraphicsEngine()
{
	this->SwapChain = 0;
	this->Device = 0;
	this->DeviceContext = 0;
	this->RenderTargetView = 0;
	this->BackBufferPtr = 0;
	this->DepthStencilBuffer = 0;
	this->DepthStencilState = 0;
	this->DepthStencilView = 0;
	this->RasterState = 0;
	this->DepthDisabledStencilState = 0;
	this->AdditiveBlendState = 0;
	this->AlphaEnableBlendingState = 0;
	this->AlphaToCoverageEnableBlendState = 0;
	this->AlphaDisableBlendingState = 0;
}

GraphicsEngine::~GraphicsEngine()
{
	this->Release();
}

void GraphicsEngine::BeginRender(float r, float g, float b, float a)
{
	float color[4];
	color[0] = r; color[1] = g; color[2] = b; color[3] = a;
	// Clear the back buffer.
	DeviceContext->ClearRenderTargetView(RenderTargetView, color);
	// Clear the depth buffer.
	DeviceContext->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void GraphicsEngine::EndRender()
{
	// Present the back buffer to the screen since rendering is complete
	if(this->VSyncEnabled)
	{
		// Lock to screen refresh rate
		SwapChain->Present(1, 0);
	}
	else
	{
		// Present as fast as possible
		SwapChain->Present(0, 0);
	}

	return;
}

void GraphicsEngine::GetDeviceInfo(int screenWidth, int screenHeight)
{
	HRESULT result;
	IDXGIFactory *factory;
	IDXGIAdapter *adapter;
	IDXGIOutput *adapterOutput;
	unsigned int numModes, i, stringLength;
	DXGI_MODE_DESC *displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	int error;


	// Before initializing Direct3D we have to get the refresh rate from the video card/monitor
	// because each computer is slightly different due to which we have to query for that info.

	// Create the directX graphics interface factory
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if(FAILED(result))
	{
		return;
	}

	// Use the factory to create an adapter for the primary graphics interface(video card)
	result = factory->EnumAdapters(0, &adapter);
	if(FAILED(result))
	{
		return;
	}

	// Enumerate the primary adapter output(monitor)
	result = adapter->EnumOutputs(0, &adapterOutput);
	if(FAILED(result))
	{
		return;
	}

	// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for
	// the adapter output (monitor).
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if(FAILED(result))
	{
		return;
	}

	// Create a list to hold all the possible display modes for this monitor/video card combination.
	displayModeList = new DXGI_MODE_DESC[numModes];
	if(!displayModeList)
	{
		return;
	}

	// Now fill the display mode list structures.
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if(FAILED(result))
	{
		return;
	}

	// Now go through all the display modes and find the one that matches the screen width and height.
	// When a match is found store the numerator and denominator of the refresh rate for that monitor.
	for(i = 0; i < numModes; i++)
	{
		if(displayModeList[i].Width == (unsigned int)screenWidth)
		{
			if(displayModeList[i].Height == (unsigned int)screenHeight)
			{
				Numerator = displayModeList[i].RefreshRate.Numerator;
				Denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	// Get the adapter (video card) description.
	result = adapter->GetDesc(&adapterDesc);
	if(FAILED(result))
	{
		return;
	}

	// Store the dedicated video card memory in megabytes.
	VideoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	// Convert the name of the video card to a character array and store it.
	error = wcstombs_s(&stringLength, VideoCardDescription, 128, adapterDesc.Description, 128);
	if(error != 0)
	{
		return;
	}

	// Release the display mode list.
	SAFE_DELETE_ARRAY(displayModeList);

	// Release the adapter output.
	adapterOutput->Release();
	adapterOutput = 0;

	// Release the adapter
	adapter->Release();
	adapter = 0;

	// Release the factory
	factory->Release();
	factory = 0;
}

void GraphicsEngine::CreateDevice(int screenWidth, int screenHeight, bool vsync, HWND hWnd, WindowModeType winMode)
{
	HRESULT result;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11Texture2D *backBufferPtr;

	this->VSyncEnabled = vsync;

	// Now that we have the refresh rate from the system we can start the directx initialization.
	
	// Initialize the swap chain description
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	// Set to a single back buffer.
	swapChainDesc.BufferCount = 1;

	// Set the width and height of the back buffer.
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;

	// Set regular 32 bit surface for the back buffer.
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Next part of swap chain description is the refresh rate. If vsync is set to true then this will lock
	// the refresh rate to system settings for e.g 60 hz. If vsync is set to false then it will draw the
	// screen as many times a second as it can, however this can cause some visual artifacts.

	// Set the refresh rate of the back buffer
	if(this->VSyncEnabled)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = Numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = Denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	// Set the usage of the back buffer.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// Set the handle for the window to render to
	swapChainDesc.OutputWindow = hWnd;

	// Turn multisampling off.
	swapChainDesc.SampleDesc.Count = 4;
	swapChainDesc.SampleDesc.Quality = 0;

	if(winMode == WMT_FULLSCREEN)
	{
		swapChainDesc.Windowed = false;
	}
	else
	{
		swapChainDesc.Windowed = true;
	}

	// Set the scan line ordering and scaling to unspecified.
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Discard the back buffer contents after presenting.
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Dont set the advanced flags.
	swapChainDesc.Flags = 0;

	// Set the feature level to directx 11
	featureLevel = D3D_FEATURE_LEVEL_11_0;

	//cout<<"Creating Device And Swap Chain"<<endl;

	// Create the swap chain, Direct3D device and Direct3D device context.
	result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel,
										   1, D3D11_SDK_VERSION, &swapChainDesc, &SwapChain, &Device,
										   NULL, &DeviceContext);	
	if(FAILED(result))
	{
		cout<<"Failed to Create Device And Swap Chain"<<endl;
		return;
	}

	cout<<"Successfully Created Device"<<endl;
}

void GraphicsEngine::CreateBuffers(int screenWidth, int screenHeight)
{
	HRESULT result;	
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_BLEND_DESC blendStateDescription;

	// Get the pointer to the back buffer
	result = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBufferPtr);
	if(FAILED(result))
	{
		return;
	}

	// Create the render target view with the back buffer pointer.
	result = Device->CreateRenderTargetView(BackBufferPtr, NULL, &RenderTargetView);
	if(FAILED(result))
	{
		return;
	}

	// Release pointer to the back buffer as we no longer need it.
	BackBufferPtr->Release();
	BackBufferPtr = 0;

	// Now we will create depth buffer and stencil buffer. stencil buffer can achieve effects
	// such as motion blur, volumetric shadows etc.

	// Initialize the description of the depth buffer.
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = screenWidth;
	depthBufferDesc.Height = screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 4;
	depthBufferDesc.SampleDesc.Quality = 1;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	// Now we create the depth and stencil using the desc. A Buffer is just a 2D texture,
	// because once our polygons are sorted and then rasterized they just end up being
	// colored pixels in this 2D buffer. Then this buffer is drawn to the screen.

	// Create the texture for the depth buffer using the filled out description.
	result = Device->CreateTexture2D(&depthBufferDesc, NULL, &DepthStencilBuffer);
	if(FAILED(result))
	{
		return;
	}

	// Now we do depth stencil description, which allows us to control what type of depth test
	// Direct3D will do for each pixel.

	// Initialize the description of the stencil state.
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	result = Device->CreateDepthStencilState(&depthStencilDesc, &DepthStencilState);
	if(FAILED(result))
	{
		return;
	}

	// Set the depth stencil state
	DeviceContext->OMSetDepthStencilState(DepthStencilState, 1);

	// Initialize the depth stencil view.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	result = Device->CreateDepthStencilView(DepthStencilBuffer, &depthStencilViewDesc, &DepthStencilView);
	if(FAILED(result))
	{
		return;
	}

	// Bind the render target view and depth stencil buffer to the output render pipeline.
	DeviceContext->OMSetRenderTargets(1, &RenderTargetView, DepthStencilView);

	// Setup the raster description which will determine how and what polygons will be drawn.
	RasterDescription.AntialiasedLineEnable = true;
	RasterDescription.CullMode = D3D11_CULL_BACK;
	RasterDescription.DepthBias = 0;
	RasterDescription.DepthBiasClamp = 0.0f;
	RasterDescription.DepthClipEnable = true;
	RasterDescription.FillMode = D3D11_FILL_SOLID;
	RasterDescription.FrontCounterClockwise = false;
	RasterDescription.MultisampleEnable = true;
	RasterDescription.ScissorEnable = false;
	RasterDescription.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	result = Device->CreateRasterizerState(&RasterDescription, &RasterState);
	if(FAILED(result))
	{
		return;
	}

	// Now set the rasterizer state.
	DeviceContext->RSSetState(RasterState);

	// Setup the ViewPort for rendering.
	ViewPort.Width = (float)screenWidth;
	ViewPort.Height = (float)screenHeight;
	ViewPort.MinDepth = 0.0f;
	ViewPort.MaxDepth = 1.0f;
	ViewPort.TopLeftX = 0.0f;
	ViewPort.TopLeftY = 0.0f;

	// Create the view port.
	DeviceContext->RSSetViewports(1, &ViewPort);
}

void GraphicsEngine::Release()
{
	// Before shutting down set to windowed mode or when you release
	// the swap chain it will throw an exception.
	if(SwapChain)
	{
		SwapChain->SetFullscreenState(false, NULL);
	}

	if(AlphaEnableBlendingState)
	{
		AlphaEnableBlendingState->Release();
		AlphaEnableBlendingState = 0;
	}

	if(AlphaToCoverageEnableBlendState)
	{
		AlphaToCoverageEnableBlendState->Release();
		AlphaToCoverageEnableBlendState = 0;
	}

	if(AdditiveBlendState)
	{
		AdditiveBlendState->Release();
		AdditiveBlendState = 0;
	}

	if(AlphaDisableBlendingState)
	{
		AlphaDisableBlendingState->Release();
		AlphaDisableBlendingState = 0;
	}


	if(DepthDisabledStencilState)
	{
		DepthDisabledStencilState->Release();
		DepthDisabledStencilState = 0;
	}

	if(RasterState)
	{
		RasterState->Release();
		RasterState = 0;
	}

	if(DepthStencilView)
	{
		DepthStencilView->Release();
		DepthStencilView = 0;
	}

	if(DepthStencilState)
	{
		DepthStencilState->Release();
		DepthStencilState = 0;
	}

	if(DepthStencilBuffer)
	{
		DepthStencilBuffer->Release();
		DepthStencilBuffer = 0;
	}

	if(RenderTargetView)
	{
		RenderTargetView->Release();
		RenderTargetView = 0;
	}

	if(DeviceContext)
	{
		DeviceContext->Release();
	}

	if(Device)
	{
		Device->Release();
		Device = 0;
	}

	if(SwapChain)
	{
		SwapChain->Release();
		SwapChain = 0;
	}
}