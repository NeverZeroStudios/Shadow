#pragma once
#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>
#include <wrl/client.h>
#include "../Windows/Window.h"
#include "../ShadowDebugger/Log.h"

namespace ShadowEngine {
	class SHADOW_API Graphics {
	public:
		bool Init(Window& window);
		bool InitDirectX();
		void Update();
		void Render();


		IDXGISwapChain* GetSwapChain();
		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContext();
		ID3D11RenderTargetView* GetRenderTargetView();
		
	private:
		Window* pWindow;
		IDXGISwapChain* swapChain;
		ID3D11Device* device;
		ID3D11DeviceContext* deviceContext;
		ID3D11RenderTargetView* renderTargetView;
	};
}