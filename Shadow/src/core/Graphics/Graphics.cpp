#include "Graphics.h"

namespace ShadowEngine {

	// basic Vertex Struct
	// position --> 12 bytes
	struct Vertex    //Overloaded Vertex Structure
	{
		Vertex() {}
		Vertex(float x, float y, float z)
			: position(x, y, z) {}

		DirectX::XMFLOAT3 position;
	};

	int color_RED[4]{ 256, 0, 0, 255 };
	int color_GREEN[4]{ 0, 255, 0, 255 };
	int color_BLUE[4]{ 0, 0, 255, 255 };

	int color_STORM[4]{ 76, 74, 72, 255 };
	int color_DARKSTORM[4]{ 12, 12, 255, 0 };
	int color_MAGENTA[4]{ 255, 0, 255, 255 };
	int color_CYAN[4]{ 0, 255, 255, 255 };
	int color_YELLOW[4]{ 255, 255, 0, 255 };




	bool Graphics::Init(Window& window)
	{
		pWindow = &window;

		if (!InitDirectX()) {
			return false;
		}

		return true;
	}
	/*
	* DXGI_FORMAT_R8G8B8A8_UNORM
	A four-component, 32-bit unsigned-normalized-integer format that supports 8 bits per channel including alpha.
		** not garanteed to be in this order

		 uint 0b 0000 0000  0000 0000  0000 0000 0000 0000
				|	 red   |  green  |	  blue	|  alpha  |

			giving us 2^32 = 4,294,967,296 color combos

			for instance
				0b 0000 1111  0000 0000  0000 0000 1111 1111

			would result a dark red color in the buffer
			while
				0b 0000 1111  0000 0000  0000 0000  0000 0000

			would resukt in a transparent color becaue there is no alpha channel

	*/

	bool Graphics::InitDirectX()
	{
		// Describe the Buffer
		DXGI_MODE_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

		bufferDesc.Width = pWindow->GetClientSize().left + pWindow->GetClientSize().right;
		bufferDesc.Height = pWindow->GetClientSize().top + pWindow->GetClientSize().bottom;
		bufferDesc.RefreshRate.Numerator = 60;
		bufferDesc.RefreshRate.Denominator = 1;
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		// Describe SwapChain
		DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
		ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

		swapChainDesc.BufferDesc = bufferDesc;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.OutputWindow = pWindow->GetWindow();
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		// Create SwapChain
		HRESULT hr = D3D11CreateDeviceAndSwapChain(
			NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			NULL,
			NULL,
			NULL,
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&pSwapChain,
			&pDevice,
			NULL,
			&pDeviceContext
		);

		if (FAILED(hr)) {
			_com_error error(hr);
			SH_DEBUGGER_FATAL("Could not initilize Direct X 11 Device context or SwapChain");
			return false;
		}

		// Create Back Buffer
		ID3D11Texture2D* backBuffer;
		hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
		if (FAILED(hr)) {
			SH_DEBUGGER_FATAL("Back Buffer Creation Failed");
			return false;
		}


		//////////////***************** OUTPUT MERGER *****************/////////////////////
		// Create Render Target
		pDevice->CreateRenderTargetView(backBuffer, NULL, &pRenderTargetView);
		backBuffer->Release();



		//////////////***************** END OUTPUT MERGER *****************/////////////////////

		return true;
	}

	void Graphics::ClearBuffer(float r, float g, float b)
	{
		float clear_color[] = { r, g, b, 1.0f };
		pDeviceContext->ClearRenderTargetView(pRenderTargetView, clear_color);
	}

	void Graphics::Draw()
	{
		DrawTest();
	}
	void Graphics::DrawTest()
	{
		//////////////***************** INPUT ASSEMBLER *****************/////////////////////
		// Create Buffers

		// Set Data
		const Vertex vertices[]{
			{ 0.0f,  0.5f, 0.5f},
			{ 0.5f, -0.5f, 0.5f},
			{-0.5f, -0.5f, 0.5f},
		};

		// Create Buffer Description
		D3D11_BUFFER_DESC vBuff_desc;
		ZeroMemory(&vBuff_desc, sizeof(vBuff_desc));

		vBuff_desc.Usage = D3D11_USAGE_DEFAULT;
		vBuff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vBuff_desc.ByteWidth = sizeof(vertices);
		vBuff_desc.StructureByteStride = sizeof(Vertex);
		vBuff_desc.CPUAccessFlags = 0;
		vBuff_desc.MiscFlags = 0;

		// Create SubresourceData
		D3D11_SUBRESOURCE_DATA vBuff_resourceData;
		ZeroMemory(&vBuff_resourceData, sizeof(vBuff_resourceData));
		vBuff_resourceData.pSysMem = vertices; // set the vertices to the subResourceData

		// Create Buffer
		HRESULT hr = pDevice->CreateBuffer(&vBuff_desc, &vBuff_resourceData, &pVertexBuffer);

		if (FAILED(hr)) {
			std::wstringstream ss;
			_com_error err(hr);
			ss << "[ERROR]\n" << "Could Not Create Vertex Buffer.\n" << "Error Description:\n" << err.ErrorMessage() << std::endl;
			SH_DEBUGGER_FATAL(ss.str().c_str());
			//return false;

		}

		// Set Vertex Buffer
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		pDeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);

		// Get Shaders

		//////////////***************** PIXEL SHADER *****************/////////////////////

		hr = D3DReadFileToBlob(L"../bin/Debug-x64/Shadow/PixelShader.cso", &pixelShaderByteCode);

		if (FAILED(hr)) {
			_com_error error(hr);
			std::wstringstream ss;
			ss << "Could not find Pixel Shader\n" << "Error Description: " << error.ErrorMessage() << std::endl;
			SH_DEBUGGER_FATAL(ss.str().c_str());
			//return false;
		}

		hr = pDevice->CreatePixelShader(pixelShaderByteCode->GetBufferPointer(), pixelShaderByteCode->GetBufferSize(), NULL, &pPixelShader);

		if (FAILED(hr)) {
			_com_error error(hr);
			std::wstringstream ss;
			ss << "Could not Create Pixel Shader\n" << "Error Description: " << error.ErrorMessage() << std::endl;
			SH_DEBUGGER_FATAL(ss.str().c_str());
			//return false;
		}

		pDeviceContext->PSSetShader(pPixelShader, nullptr, 0);

		//////////////***************** END PIXEL SHADER *****************/////////////////////


		//////////////***************** VERTEX SHADER *****************/////////////////////

		hr = D3DReadFileToBlob(L"../bin/Debug-x64/Shadow/VertexShader.cso", &vertexShaderByteCode);

		if (FAILED(hr)) {
			_com_error error(hr);
			std::wstringstream ss;

			ss << "Could not find Vertex Shader\n" << "Error Description: " << error.ErrorMessage() << std::endl;
			SH_DEBUGGER_FATAL(ss.str().c_str());
			//return false;
		}

		hr = pDevice->CreateVertexShader(vertexShaderByteCode->GetBufferPointer(), vertexShaderByteCode->GetBufferSize(), NULL, &pVertexShader);

		if (FAILED(hr)) {
			_com_error error(hr);
			std::wstringstream ss;
			ss << "Could not Create Vertex Shader\n" << "Error Description: " << error.ErrorMessage() << std::endl;
			SH_DEBUGGER_FATAL(ss.str().c_str());
			//return false;
		}

		pDeviceContext->VSSetShader(pVertexShader, nullptr, 0);


		//////////////***************** END VERTEX SHADER *****************/////////////////////
		const D3D11_INPUT_ELEMENT_DESC inputLayout[]{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		int numElements = ARRAYSIZE(inputLayout);


		hr = pDevice->CreateInputLayout(inputLayout, numElements, vertexShaderByteCode->GetBufferPointer(), vertexShaderByteCode->GetBufferSize(), &pInputLayout);

		if (FAILED(hr)) {
			std::wstringstream ss;
			_com_error err(hr);
			ss << "[ERROR]\n" << "Could Not Initilize Input Layout.\n" << "Error Description:\n" << err.ErrorMessage() << std::endl;
			SH_DEBUGGER_FATAL(ss.str().c_str());// <-- KINDA ANNOYING... CREATE A OVERLOAD FOR USE WITH STD::STRINGS
			//return false;

		}

		pDeviceContext->IASetInputLayout(pInputLayout);

		pDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);


		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//////////////***************** END INPUT ASSEMBLER *****************/////////////////////



		//////////////***************** RASTERIZER STAGE *****************/////////////////////

		D3D11_VIEWPORT viewport;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.MinDepth = 0;
		viewport.MaxDepth = 1;
		viewport.Width = pWindow->GetClientSize().left + pWindow->GetClientSize().right;
		viewport.Height = pWindow->GetClientSize().top + pWindow->GetClientSize().bottom;
		pDeviceContext->RSSetViewports(1, &viewport);

		//////////////***************** END RASTERIZE STAGE *****************/////////////////////
		SH_DEBUGGER_INFO("End of Render Test");
		pDeviceContext->Draw(3, 0);

	}

	float convertIntToFloat(int n, int d) {
		return (n * 1.0f) / d;
	}

	float* Graphics::ConvertColor4(int oldColor[4]) {

		float newColor[4] = { 0 };

		for (int i = 0; i < 4; i++)
		{
			newColor[i] = (oldColor[i] * 1.0f) / 255;
		}

		return newColor;
	}

	int* AddColors(int* color_a, int* color_b) {
		int newColor[4] = { 0 };


		int n_r = color_a[0] + color_b[0];
		if (n_r > 255) n_r = 255;

		int n_g = color_a[1] + color_b[1];
		if (n_g > 255) n_g = 255;

		int n_b = color_a[2] + color_b[2];
		if (n_b > 255) n_b = 255;

		int n_a = color_a[3] + color_b[3];
		if (n_a > 255) n_a = 255;

		newColor[0] = n_r;
		newColor[1] = n_g;
		newColor[2] = n_b;
		newColor[3] = n_a;

		return newColor;
	}

	void Graphics::EndFrame()
	{
		if (FAILED(pSwapChain->Present(1u, 0))) {
			SH_DEBUGGER_FATAL("FAILED TO FLIP BUFFERS");
		}
		SH_DEBUGGER_INFO("RENDER FINISHED");

	}

	void Graphics::Cleanup()
	{
		// Clean up COM objects
		pSwapChain->Release();
		pDeviceContext->Release();
		pDevice->Release();
		pRenderTargetView->Release();
		pVertexBuffer->Release();
		pVertexShader->Release();
		pPixelShader->Release();

		vertexShaderByteCode->Release();
		pixelShaderByteCode->Release();

		pInputLayout->Release();

	}

	IDXGISwapChain* Graphics::GetSwapChain()
	{
		return pSwapChain;
	}

	ID3D11Device* Graphics::GetDevice()
	{
		return pDevice;
	}

	ID3D11DeviceContext* Graphics::GetDeviceContext()
	{
		return pDeviceContext;
	}

	ID3D11RenderTargetView* Graphics::GetRenderTargetView()
	{
		return pRenderTargetView;
	}

	ID3D11Buffer* Graphics::GetVertexBuffer()
	{
		return pVertexBuffer;
	}

}