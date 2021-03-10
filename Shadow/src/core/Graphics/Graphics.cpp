#include "Graphics.h"
#include <comdef.h>

bool ShadowEngine::Graphics::Init(Window& window)
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



bool ShadowEngine::Graphics::InitDirectX()
{
	// Describe the Buffer
	DXGI_MODE_DESC bufferDesc = { 0 };

	bufferDesc.Width = pWindow->GetClientSize().left + pWindow->GetClientSize().right;
	bufferDesc.Height = pWindow->GetClientSize().top + pWindow->GetClientSize().bottom;
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.RefreshRate.Denominator = 1;
	
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Describe SwapChain
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
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
		&swapChain,
		&device,
		NULL,
		&deviceContext
	);

	if (FAILED(hr)) {
		_com_error error(hr);
		SH_DEBUGGER_FATAL("Could not initilize Direct X 11 Device context or SwapChain");
		return false;
	}

	// Create Back Buffer
	ID3D11Texture2D* backBuffer;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	if (backBuffer == 0) {
		SH_DEBUGGER_FATAL("Back Buffer Creation Failed");
		return false;
	}
	// Create Render Target
	device->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
	backBuffer->Release();

	deviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);

	return true;
}
static float r = 0.0f;
static float g = 0.0f;
static float b = 0.0f;

static int colormodr = 1;
static int colormodg = 1;
static int colormodb = 1;
void ShadowEngine::Graphics::Update()
{
	SH_DEBUGGER_INFO("GFX UPDATE");

}

/*
	 n		x
	--- = -----
	 d	   1.0f

 x =  n * 1.0f
	  -------
		d
*/

float convertIntToFloat(int n, int d) {
	return (n * 1.0f) / d;
}

float* ConvertColor4(int oldColor[4]) {

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

void ShadowEngine::Graphics::Render()
{
	int color_RED[4]{ 256, 0, 0, 255 };
	int color_GREEN[4]{ 0, 255, 0, 255 };
	int color_BLUE[4]{ 0, 0, 255, 255 };

	int color_STORM[4]{ 76, 74, 72, 255 };
	int color_MAGENTA[4]{ 255, 0, 255, 255 };
	int color_CYAN[4]{ 0, 255, 255, 255 };
	int color_YELLOW[4]{ 255, 255, 0, 255 };



	float* clear_color = ConvertColor4(AddColors(color_RED, color_MAGENTA));
	deviceContext->ClearRenderTargetView(renderTargetView, clear_color);

	swapChain->Present(0, 0);
	SH_DEBUGGER_INFO("GFX RENDER");
}

IDXGISwapChain* ShadowEngine::Graphics::GetSwapChain()
{
	return swapChain;
}

ID3D11Device* ShadowEngine::Graphics::GetDevice()
{
	return device;
}

ID3D11DeviceContext* ShadowEngine::Graphics::GetDeviceContext()
{
	return deviceContext;
}

ID3D11RenderTargetView* ShadowEngine::Graphics::GetRenderTargetView()
{
	return renderTargetView;
}
