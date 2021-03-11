#include "Window.h"
#include "../ShadowDebugger/Log.h"

namespace ShadowEngine {

    BOOL Window::Create(PCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu)
    {
        WNDCLASS wc = { 0 };

        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = ClassName();

        RegisterClass(&wc);

        _hWnd = CreateWindowEx(
            dwExStyle, 
            ClassName(), 
            lpWindowName, 
            dwStyle, 
            x, 
            y,
            nWidth, 
            nHeight, 
            hWndParent, 
            hMenu, 
            GetModuleHandle(NULL),
            this
        );
        
        GetWindowRect(_hWnd, &windowRect);
        GetClientRect(_hWnd, &clientRect);

        if (_hWnd == NULL)
            return false;

        return true;
    }

    PCWSTR Window::ClassName() const
    {
        return L"WINDOW";
    }

    LRESULT Window::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg) {
            case WM_DESTROY:
                SH_DEBUGGER_INFO("GOOD BYE!");
                PostQuitMessage(0);
                break;
            default:
                return DefWindowProc(_hWnd, uMsg, wParam, lParam);
                break;
        }
    }

    std::optional<int> Window::ProcessMessages()
    {
        MSG msg;
        ZeroMemory(&msg, sizeof(MSG));

        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                return msg.wParam;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
           
        }

        return {};
    }

    RECT Window::GetWindowSize()
    {
        return windowRect;
    }

    RECT Window::GetClientSize()
    {
        return clientRect;
    }

}