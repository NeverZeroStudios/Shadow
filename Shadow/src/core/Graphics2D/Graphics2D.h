#pragma once
#include "../Core.h"
#include "../ShadowDebugger/Log.h"

#pragma comment(lib, "d2d1.lib")

// C RunTime Header Files:
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>

#include <comdef.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

namespace ShadowEngine {

	class SHADOW_API Graphics2D {
	public:
		~Graphics2D();
		void Cleanup();
		
		bool Init(HWND& hWnd);
		bool InitD2D();
		
		bool Render(HWND hWnd);
		bool CreateResources(HWND& hWnd);

		void OnResize(UINT newWidth, UINT newHeight);

		ID2D1Factory* GetFactory() { return pD2DFactory; }
	private:
		// required to start rendering
		ID2D1Factory* pD2DFactory = nullptr;
		ID2D1HwndRenderTarget* pRenderTarget = nullptr;

		// brushes for drawing
		ID2D1SolidColorBrush* brush_GRAY = nullptr;
		ID2D1SolidColorBrush* brush_BLUE = nullptr;
	};

}