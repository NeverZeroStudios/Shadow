#pragma once

#include "../core.h"
#include "../Windows/Window.h"
#include "../ShadowDebugger/Log.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#include <wrl/client.h>
#include <comdef.h>

namespace ShadowEngine {
	class SHADOW_API Graphics {
	public:
		bool Init(Window& window);
		bool InitDirectX();

		void ClearBuffer(float r, float g, float b);

		void Draw();

		void DrawTest();

		void EndFrame();

		void Cleanup();

		IDXGISwapChain* GetSwapChain();
		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContext();
		ID3D11RenderTargetView* GetRenderTargetView();
		
		ID3D11Buffer* GetIndexBuffer();
		ID3D11Buffer* GetVertexBuffer();

	private: // private functions
		float* ConvertColor4(int oldColor[4]);
		
	private: // private COM ptrs
		Window* pWindow;

		// d3d11
		IDXGISwapChain* pSwapChain;
		ID3D11Device* pDevice;
		ID3D11DeviceContext* pDeviceContext;
		ID3D11RenderTargetView* pRenderTargetView;
	
		ID3D11Buffer* pVertexBuffer;
		ID3D11Buffer* pIndexBuffer;

		ID3DBlob* pBlob;
		//ID3DBlob* pixelShaderByteCode;

		ID3D11VertexShader* pVertexShader;
		ID3D11PixelShader* pPixelShader;

		ID3D11InputLayout* pInputLayout;

	};
}