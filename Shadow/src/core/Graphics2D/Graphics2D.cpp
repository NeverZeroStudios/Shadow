#include "Graphics2D.h"

namespace ShadowEngine {

    Graphics2D::~Graphics2D()
    {
        
    }

    void Graphics2D::Cleanup() {
        pRenderTarget->Release();
        brush_BLUE->Release();
        brush_GRAY->Release();
    }

    bool Graphics2D::Init(HWND& hWnd)
    {
        if (!InitD2D()) {

            std::wstringstream ss;
            ss << "Could Not Create D2D Factory." << std::endl;
            SH_DEBUGGER_ERR(ss.str().c_str());
            return false;
           

        }

        
        if (!CreateResources(hWnd)) {
            std::wstringstream ss;
            ss << "Could Not Create Resources..." << std::endl;
            SH_DEBUGGER_ERR(ss.str().c_str());
            return false;
        }
        
        return true;
    }
    


    bool Graphics2D::InitD2D() {
        
        // Initilize DirectX Factory 
        HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
        if (FAILED(hr)) {
            return false;
        }

        // initilize D2D Text Factory

        return true;

    }

    bool Graphics2D::CreateResources(HWND& hWnd)
    {
        HRESULT hr = S_OK;

        if (pRenderTarget == nullptr) { // if a render target does not exist then this is the first time this function has run

            // get the size of the client rectangle 
            RECT client;
            GetClientRect(hWnd, &client);

            // determine size of view port
            D2D1_SIZE_U vp_size = D2D1::SizeU(client.right - client.left, client.bottom - client.top);

            // create render target
            hr = pD2DFactory->CreateHwndRenderTarget(
                D2D1::RenderTargetProperties(),
                D2D1::HwndRenderTargetProperties(hWnd, vp_size),
                &pRenderTarget
            );

            if (FAILED(hr)) {
                SH_DEBUGGER_ERR("Could Not Create RenderTarget View");
                return false;
            }

            // create gray brush
            hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSlateGray), &brush_GRAY);
            if (FAILED(hr)) {
                return false;
            }
            // create blue brush
            hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::CornflowerBlue), &brush_BLUE);
            if (FAILED(hr)) {
                return false;
            }
        }
   
        return true;
    }


    void Graphics2D::OnResize(UINT newWidth, UINT newHeight) {
        if (pRenderTarget)
        {
            pRenderTarget->Resize(D2D1::SizeU(newWidth, newHeight));
        }
    }

    bool Graphics2D::Render(HWND hWnd)
    {   

        if (CreateResources(hWnd)) {
            pRenderTarget->BeginDraw();

            pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
            pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

            D2D1_SIZE_F rtSize = pRenderTarget->GetSize();
            int width = static_cast<int>(rtSize.width);
            int height = static_cast<int>(rtSize.height);

            for (int x = 0; x < width; x += 16)
            {
                pRenderTarget->DrawLine(
                    D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
                    D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
                    brush_GRAY,
                    0.5f
                );
            }

            for (int y = 0; y < height; y += 16)
            {
                pRenderTarget->DrawLine(
                    D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
                    D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
                    brush_GRAY,
                    0.5f
                );
            }

            D2D1_RECT_F rectangle1 = D2D1::RectF(
                rtSize.width / 2 - 50.0f,
                rtSize.height / 2 - 50.0f,
                rtSize.width / 2 + 50.0f,
                rtSize.height / 2 + 50.0f
            );

            D2D1_RECT_F rectangle2 = D2D1::RectF(
                rtSize.width / 2 - 100.0f,
                rtSize.height / 2 - 100.0f,
                rtSize.width / 2 + 100.0f,
                rtSize.height / 2 + 100.0f
            );

            pRenderTarget->FillRectangle(&rectangle1, brush_GRAY); // fill rect will draw filled rect
            pRenderTarget->DrawRectangle(&rectangle2, brush_BLUE); // draw rect will draw outline


            HRESULT hr = pRenderTarget->EndDraw();
          
            if (hr == D2DERR_RECREATE_TARGET) {
                Cleanup();
            }
        }

        return true;
    }

}
