#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

#include <qwidget.h>

class GraphicsEngine
{
	private:
			bool VSyncEnabled;
			int VideoCardMemory;
			char VideoCardDescription[128];
			
			ID3D11Texture2D *BackBufferPtr;
			ID3D11RenderTargetView *RenderTargetView;
			ID3D11Texture2D	*DepthStencilBuffer;
			ID3D11DepthStencilState *DepthStencilState;
			ID3D11DepthStencilView *DepthStencilView;
			ID3D11RasterizerState *RasterState;
			ID3D11DepthStencilState *DepthDisabledStencilState;
			ID3D11BlendState *AlphaEnableBlendingState;
			ID3D11BlendState *AlphaToCoverageEnableBlendState;
			ID3D11BlendState *AdditiveBlendState;
			ID3D11BlendState *AlphaDisableBlendingState;
			D3D11_RASTERIZER_DESC RasterDescription;
			D3D11_VIEWPORT ViewPort;	
			unsigned int Numerator;
			unsigned int Denominator;
	public:
			ID3D11Device *Device;
			ID3D11DeviceContext *DeviceContext;
			IDXGISwapChain *SwapChain;
			DXGI_SWAP_CHAIN_DESC SwapChainDesc;

			Matrix4x4f ViewMatrix;
			Matrix4x4f ProjectionMatrix;
		//	aiScene *scene;
	public:
			GraphicsEngine();
			~GraphicsEngine();

			void BeginRender(float r, float g, float b, float a);
			void EndRender();

			void GetDeviceInfo(int screenWidth, int screenHeight);
			void CreateDevice(int screenWidth, int screenHeight, bool vsync, HWND wId, WindowModeType winMode);
			void CreateBuffers(int screenWidth, int screenHeight);
			void Release();
			void ReleaseBuffers();
};

#endif 