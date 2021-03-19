#pragma once

#include "../core.h"
#include "../Windows/Window.h"
#include "../ShadowDebugger/Log.h"

#include "../../util/Utilities.h"


#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h> 
#include <DirectXMath.h> 
#include <d3dcompiler.h> SHADOW_API

#include <wrl/client.h> SHADOW_API
#include <comdef.h> 

namespace ShadowEngine {
	class SHADOW_API Graphics {
	public:
		bool Init(Window& window);
		bool InitDirectX();

		void ClearBuffer(float r, float g, float b);

		void Update(float dt);

		void UpdateTest(float dt);

		void EndFrame();

		void Cleanup();

		IDXGISwapChain* GetSwapChain();
		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContext();
		ID3D11RenderTargetView* GetRenderTargetView();
		
		ID3D11Buffer* GetIndexBuffer();
		ID3D11Buffer* GetVertexBuffer();

		ID3D11RasterizerState* GetRasterizerState();
		bool SetRasterizerState(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode);

	private: // private functions
		float* ConvertColor4(int oldColor[4]);
				
	private: // private COM ptrs
		Window* pWindow;
		
		struct SHADOW_API cbPerObject {
			DirectX::XMMATRIX WVP;
		};

		// d3d11
		IDXGISwapChain* pSwapChain;
		ID3D11Device* pDevice;
		ID3D11DeviceContext* pDeviceContext;
		ID3D11RenderTargetView* pRenderTargetView;
	
		ID3D11Buffer* pVertexBuffer;
		ID3D11Buffer* pIndexBuffer;

		ID3DBlob* pBlob;

		ID3D11VertexShader* pVertexShader;
		ID3D11PixelShader* pPixelShader;

		ID3D11InputLayout* pInputLayout;

		ID3D11DepthStencilView* pDepthStencilView;
		ID3D11Texture2D* pDepthStencilBuffer;

		// constant buffer
		ID3D11Buffer* pConstantBuffer;
		cbPerObject cbPerObjectBuffer;

		DirectX::XMMATRIX wvp;
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;

		//DirectX::XMVECTOR* camPos;
		//DirectX::XMVECTOR* camTarget;
		//DirectX::XMVECTOR* camUp;


		// render state
		ID3D11RasterizerState* pRasterizerState;
	};
}