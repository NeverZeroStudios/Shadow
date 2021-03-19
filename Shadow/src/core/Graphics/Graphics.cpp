#include "Graphics.h"

namespace ShadowEngine {

	// basic Vertex Struct
	// position --> 12 bytes
	struct Vertex    //Overloaded Vertex Structure
	{
		struct { // float3 4 bytes * 3 = 12 bytes
			float x;
			float y;
			float z;
		}position;
		//float pad;// 4bytes + 12bytes = 16 ] // END BLOCK
		struct { // float3 4 bytes * 4 = 16 bytes
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		}color; //] END BLOCK
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
	float degreesToRadians(float degrees) {
		return degrees * (3.14 / 180);
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
	static float pos_z = 0;
	bool Graphics::InitDirectX()
	{
		SH_DEBUGGER_INFO("Initilizing DirectX 11");

		//////////////***************** INPUT ASSEMBLER *****************/////////////////////

		int width = pWindow->GetClientSize().left + pWindow->GetClientSize().right;
		int height = pWindow->GetClientSize().top + pWindow->GetClientSize().bottom;
		// Describe the Buffer
		DXGI_MODE_DESC buffer_desc;
		ZeroMemory(&buffer_desc, sizeof(DXGI_MODE_DESC));

		buffer_desc.Width = width;
		buffer_desc.Height = height;
		buffer_desc.RefreshRate.Numerator = 60;
		buffer_desc.RefreshRate.Denominator = 1;
		buffer_desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		buffer_desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		buffer_desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;


		DXGI_SAMPLE_DESC sample_desc{0};
		sample_desc.Count = 1;
		sample_desc.Quality = 0;

		// Describe SwapChain
		DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
		ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

		swapChainDesc.BufferDesc = buffer_desc;
		swapChainDesc.SampleDesc = sample_desc;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
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
			0,
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&pSwapChain,
			&pDevice,
			NULL,
			&pDeviceContext
		);




		if (FAILED(hr)) {
			_com_error error(hr);
			std::wstringstream ss;
			ss << "Could not initilize Direct X 11 Device context or SwapChain" << std::endl <<
				"Error Description: " << error.ErrorMessage() << std::endl;
			SH_DEBUGGER_FATAL(ss.str().c_str());
			return false;
		}

		// Create Back Buffer
		ID3D11Resource* backBuffer;
		hr = GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Resource), (void**)&backBuffer);
		if (FAILED(hr)) {
			SH_DEBUGGER_FATAL("Back Buffer Creation Failed");
			return false;
		}


		// Get Shaders
		#pragma region Pixel Shader


		//////////////***************** PIXEL SHADER *****************/////////////////////

		std::wstringstream pixel_path;
		pixel_path << Utilities::FileStructure::BuildFilePath(L"PixelShader.cso");
		hr = D3DReadFileToBlob(pixel_path.str().c_str(), &pBlob);

		if (FAILED(hr)) {
			_com_error error(hr);
			std::wstringstream ss;
			ss << "Could not find Pixel Shader\n" << "Error Description: " << error.ErrorMessage() << std::endl;
			SH_DEBUGGER_FATAL(ss.str().c_str());
			return false;
		}

		hr = GetDevice()->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &pPixelShader);



		if (FAILED(hr)) {
			_com_error error(hr);
			std::wstringstream ss;

			ss << "Could not Create Pixel Shader\n" << "Error Description: " << error.ErrorMessage() << std::endl;
			SH_DEBUGGER_FATAL(ss.str().c_str());
			return false;
		}

		pDeviceContext->PSSetShader(pPixelShader, nullptr, 0);

		//////////////***************** END PIXEL SHADER *****************/////////////////////
		#pragma endregion

		#pragma region Vertex Shader
		//////////////***************** VERTEX SHADER *****************/////////////////////
		std::wstringstream vert_path;
		vert_path << Utilities::FileStructure::BuildFilePath(L"VertexShader.cso");

		hr = D3DReadFileToBlob(vert_path.str().c_str(), &pBlob);

		if (FAILED(hr)) {
			_com_error error(hr);
			std::wstringstream ss;

			ss << "Could not find Vertex Shader\n" << "Error Description: " << error.ErrorMessage() << std::endl;
			SH_DEBUGGER_FATAL(ss.str().c_str());

			return false;
		}

		hr = GetDevice()->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &pVertexShader);

		if (FAILED(hr)) {
			_com_error error(hr);
			std::wstringstream ss;
			ss << "Could not Create Vertex Shader\n" << "Error Description: " << error.ErrorMessage() << std::endl;
			SH_DEBUGGER_FATAL(ss.str().c_str());
			return false;
		}

		pDeviceContext->VSSetShader(pVertexShader, nullptr, 0);
		vert_path.clear();

		//////////////***************** END VERTEX SHADER *****************/////////////////////
		#pragma endregion

		const D3D11_INPUT_ELEMENT_DESC inputLayout[]{
			{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "Color", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		int numElements = ARRAYSIZE(inputLayout);


		hr = GetDevice()->CreateInputLayout(inputLayout, numElements, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);

		if (FAILED(hr)) {
			std::wstringstream ss;
			_com_error err(hr);
			ss << "[ERROR]\n" << "Could Not Initilize Input Layout.\n" << "Error Description:\n" << err.ErrorMessage() << std::endl;
			SH_DEBUGGER_FATAL(ss.str().c_str());// <-- KINDA ANNOYING... CREATE A OVERLOAD FOR USE WITH STD::STRINGS
			return false;

		}

		pDeviceContext->IASetInputLayout(pInputLayout);


		const Vertex vertices[]{
			// x      y      z        r    g    b    a 
			{ 1.0f,  1.0f, 1.0f,	  255, 0, 0, 255},  // [0] +-------
			{ 1.0f, -1.0f, 1.0f,	  255, 0, 0, 255},  // [1] | FRONT
			{-1.0f, -1.0f, 1.0f,	  255, 0, 0, 255},  // [2] | 
			{-1.0f,  1.0f, 1.0f,	  255, 0, 0, 255},  // [3] +------- 

			{-1.0f,  1.0f, -1.0f,	  0, 255, 0, 255}, // [4] +-------
			{-1.0f, -1.0f, -1.0f,	  0, 255, 0, 255}, // [5] | BACK
			{ 1.0f, -1.0f, -1.0f,	  0, 255, 0, 255}, // [6] | 
			{ 1.0f,  1.0f, -1.0f,	  0, 255, 0, 255}, // [7] +------- 

			{-1.0f,  -1.0f, 1.0f,	  0, 0, 255, 255},  // [1] +-------  
			{-1.0f,  -1.0f, -1.0f,	  0, 0, 255, 255},  // [3] |
			{-1.0f,   1.0f, -1.0f,	  0, 0, 255, 255},  // [2] | LEFT
			{-1.0f,   1.0f, 1.0f,	  0, 0, 255, 255},  // [0] +-------


			{ 1.0f, 1.0f,  1.0f,	255, 255, 0, 255}, // [4] +-------
			{ 1.0f, 1.0f,  -1.0f,	255, 255, 0, 255}, // [5] | RIGHT
			{ 1.0f, -1.0f, -1.0f,	255, 255, 0, 255}, // [6] | 
			{ 1.0f, -1.0f, 1.0f,	255, 255, 0, 255}, // [7] +------- 


			{ 1.0f, -1.0f, 1.0f,	255, 0, 255, 255},   // [0] +-------
			{ 1.0f, -1.0f, -1.0f,	255, 0, 255, 255},   // [1] | BOTTOM
			{-1.0f, -1.0f, -1.0f,	255, 0, 255, 255},   // [3] |
			{-1.0f, -1.0f, 1.0f,	255, 0, 255, 255},   // [2] +-------  

			{-1.0f, 1.0f,  1.0f,	  0, 255, 255, 255}, // [5] | TOP
			{-1.0f, 1.0f, -1.0f,	  0, 255, 255, 255}, // [4] +-------
			{ 1.0f, 1.0f, -1.0f,	  0, 255, 255, 255}, // [6] | 
			{ 1.0f, 1.0f,  1.0f,	  0, 255, 255, 255},   // [7] +------- 

		};

		///////////***************  VERTEX BUFFER ***************////////////////

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
		hr = GetDevice()->CreateBuffer(&vBuff_desc, &vBuff_resourceData, &pVertexBuffer);

		if (FAILED(hr)) {
			std::wstringstream ss;
			_com_error err(hr);
			ss << "[ERROR]\n" << "Could Not Create Vertex Buffer.\n" << "Error Description:\n" << err.ErrorMessage() << std::endl;
			SH_DEBUGGER_FATAL(ss.str().c_str());
			return false;

		}

		// Set Vertex Buffer
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		pDeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);

		///////////*************  END VERTEX BUFFER *************////////////////


		///////////***************  INDEX BUFFER ***************////////////////

		const unsigned short indices[]
		{
			// FRONT
			0, 1, 2, 
			0, 2, 3, 
			// BACK
			4, 5, 6, 
			4, 6, 7,
			// LEFT 
			8, 9, 10,
			8, 10, 11,
			// RIGHT 
			12, 13, 14,
			12, 14, 15, 
			// BOTTOM
			16, 17, 18,
			16, 18, 19,
			// TOP
			20, 21, 22, 
			20, 22, 23  
		};

		D3D11_BUFFER_DESC indexBuffer_desc = { 0 };


		indexBuffer_desc.Usage = D3D11_USAGE_DEFAULT;
		indexBuffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBuffer_desc.ByteWidth = sizeof(indices);
		indexBuffer_desc.StructureByteStride = sizeof(unsigned short);

		indexBuffer_desc.CPUAccessFlags = 0;
		indexBuffer_desc.MiscFlags = 0;


		// Create SubresourceData
		D3D11_SUBRESOURCE_DATA iBuff_resoruceData = { 0 };
		iBuff_resoruceData.pSysMem = indices; // set the vertices to the subResourceData

		hr = GetDevice()->CreateBuffer(&indexBuffer_desc, &iBuff_resoruceData, &pIndexBuffer);


		pDeviceContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

		///////////*************  END INDEX BUFFER *************////////////////

		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);




		//////////////***************** END INPUT ASSEMBLER *****************/////////////////////



		//////////////***************** RASTERIZER STAGE *****************/////////////////////


		SetRasterizerState(D3D11_FILL_SOLID, D3D11_CULL_BACK);


	
		//////////////***************** END RASTERIZE STAGE *****************/////////////////////


		//////////////***************** OUTPUT MERGER *****************/////////////////////

		D3D11_TEXTURE2D_DESC depthStencilDesc = {0};
		depthStencilDesc.Width = width;
		depthStencilDesc.Height = height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc = sample_desc;

		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;

		hr = GetDevice()->CreateTexture2D(&depthStencilDesc, NULL, &pDepthStencilBuffer);
		if (FAILED(hr)) {
			SH_DEBUGGER_FATAL("COULD NOT INITILIZE DEPTH STENCIL BUFFER");
			return false;
		}

		hr = GetDevice()->CreateDepthStencilView(pDepthStencilBuffer, NULL, &pDepthStencilView);
		if (FAILED(hr)) {
			SH_DEBUGGER_FATAL("COULD NOT INITILIZE DEPTH STENCIL View");
			return false;
		}
		
		// Create Render Target
		GetDevice()->CreateRenderTargetView(backBuffer, NULL, &pRenderTargetView);
		backBuffer->Release();



		pDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, pDepthStencilView);

		D3D11_VIEWPORT viewport;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.MinDepth = 0;
		viewport.MaxDepth = 1;
		viewport.Width = width;
		viewport.Height = height;

		pDeviceContext->RSSetViewports(1, &viewport);

		//////////////***************** END OUTPUT MERGER *****************/////////////////////
	



		D3D11_BUFFER_DESC connstantBufferDesc = { 0 };
		connstantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		connstantBufferDesc.ByteWidth = sizeof(DirectX::XMMATRIX);
		connstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		connstantBufferDesc.CPUAccessFlags = 0;
		connstantBufferDesc.MiscFlags = 0;

		hr = GetDevice()->CreateBuffer(&connstantBufferDesc, NULL, &pConstantBuffer);
		if (FAILED(hr)) {
			SH_DEBUGGER_ERR("Could not Create Constant Buffer");
			return false;
		}
		//p = ;
		//u = 
		//t = 
		
		DirectX::XMVECTOR camPos	= DirectX::XMVectorSet(0.0f, 3.0f, -8.5f, 0.0f); // moves back 0.5f
		DirectX::XMVECTOR camUp		= DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		DirectX::XMVECTOR camTarget = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);  // look at 0,0,0 

		view = DirectX::XMMatrixLookAtRH(camPos, camTarget, camUp);
		projection = DirectX::XMMatrixPerspectiveFovRH(degreesToRadians(60.0f), (float)width / height, 0.01f, 1000.0f);

		SH_DEBUGGER_LOG("DirectX 11 Initilization Success");
		return true;
	}

	void Graphics::ClearBuffer(float r, float g, float b)
	{
		float clear_color[] = { r , g , b , 1.0f };
		pDeviceContext->ClearRenderTargetView(pRenderTargetView, clear_color);
		pDeviceContext->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	void Graphics::Update(float dt)
	{
		UpdateTest(dt);
	}

	


	void Graphics::UpdateTest(float dt)
	{
		
		world = DirectX::XMMatrixIdentity();
		static float rot;
		static float pos;

		// cube 0
		rot = sin(dt) / 2.0;
		pos = sin(dt) / 2.0;
		pos *= 10;
		rot *= 100;
		world =
			DirectX::XMMatrixRotationRollPitchYaw(degreesToRadians(rot), degreesToRadians(rot), degreesToRadians(rot)) *
			DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
			DirectX::XMMatrixTranslation(pos, 0, -2.0f);

		wvp = world * view * projection;

		cbPerObjectBuffer.WVP = DirectX::XMMatrixTranspose(wvp);

		pDeviceContext->UpdateSubresource(pConstantBuffer, 0, NULL, &cbPerObjectBuffer, 0, 0);

		pDeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
		
		pDeviceContext->DrawIndexed(36, 0, 0);


		// CUBE 2
		rot = sin(dt) / 2.0 + 2.0f;
		rot *= 100;

		world =
			DirectX::XMMatrixRotationRollPitchYaw(degreesToRadians(rot), degreesToRadians(rot), degreesToRadians(rot)) *
			DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
			DirectX::XMMatrixTranslation(2.0f, 0.0f, 0.0f);

		wvp = world * view * projection;

		cbPerObjectBuffer.WVP = DirectX::XMMatrixTranspose(wvp);

		pDeviceContext->UpdateSubresource(pConstantBuffer, 0, NULL, &cbPerObjectBuffer, 0, 0);

		pDeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);

		pDeviceContext->DrawIndexed(36, 0, 0);

		// CUBE 3
		rot = sin(dt) / 2.0 + 2.0f;
		rot *= 500;

		world =
			DirectX::XMMatrixRotationRollPitchYaw(degreesToRadians(rot), degreesToRadians(rot), degreesToRadians(rot)) *
			DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
			DirectX::XMMatrixTranslation(-2.0f, 0.0f, 0.0f);

		wvp = world * view * projection;

		cbPerObjectBuffer.WVP = DirectX::XMMatrixTranspose(wvp);

		pDeviceContext->UpdateSubresource(pConstantBuffer, 0, NULL, &cbPerObjectBuffer, 0, 0);

		pDeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);

		pDeviceContext->DrawIndexed(36, 0, 0);

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

	void Graphics::EndFrame()
	{
		HRESULT hr;
		if (FAILED(hr = GetSwapChain()->Present(1u, 0))) {
			SH_DEBUGGER_FATAL("FAILED TO FLIP BUFFERS");
		}
		//SH_DEBUGGER_INFO("RENDER FINISHED");

	}

	void Graphics::Cleanup()
	{
		// Clean up COM objects
		GetSwapChain()->Release();
		GetDevice()->Release();
		pDeviceContext->Release();
		pRenderTargetView->Release();
		pVertexBuffer->Release();
		pVertexShader->Release();
		pPixelShader->Release();
		pDepthStencilBuffer->Release();
		pDepthStencilView->Release();
		pBlob->Release();
		pInputLayout->Release();
		pRasterizerState->Release();
		pConstantBuffer->Release();
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

	ID3D11Buffer* Graphics::GetIndexBuffer()
	{
		return pIndexBuffer;
	}

	ID3D11Buffer* Graphics::GetVertexBuffer()
	{
		return pVertexBuffer;
	}

	ID3D11RasterizerState* Graphics::GetRasterizerState()
	{
		return pRasterizerState;
	}

	bool Graphics::SetRasterizerState(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode)
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
		desc.FillMode = fill_mode;
		desc.FillMode = fill_mode;
		desc.CullMode = cull_mode;

		HRESULT hr = GetDevice()->CreateRasterizerState(&desc, &pRasterizerState);
		
		if (FAILED(hr)) {
			SH_DEBUGGER_ERR("COULD NOT SWITCH RASTERIZER STATE");
			return false;
		}
		
		pDeviceContext->RSSetState(pRasterizerState);
		return true;
	}

}
