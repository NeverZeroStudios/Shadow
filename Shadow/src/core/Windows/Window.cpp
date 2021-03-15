#include "Window.h"
#include "windowsx.h"

#define BIT(bit)(1<<bit)
#define AT_BIT(bit) & BIT(bit)

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
        static int rp_count = 0;
        switch (uMsg) {
            case WM_DESTROY:
                PostQuitMessage(0);
                break;
#pragma region MOUSE INPUT MESSAGES

            case WM_MOUSEMOVE:
                events->Enqueue(new Events::MouseMovedEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
                break;

            case WM_LBUTTONDOWN:
                events->Enqueue(new Events::MouseClickEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), Events::MOUSE_BUTTON::LEFT));
                break;

            case WM_MBUTTONDOWN:
                events->Enqueue(new Events::MouseClickEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), Events::MOUSE_BUTTON::MIDDLE));
                break;

            case WM_RBUTTONDOWN:
                events->Enqueue(new Events::MouseClickEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), Events::MOUSE_BUTTON::RIGHT));
                break;

#pragma endregion
#pragma region KEYBOARD INPUT MESSAGES
            case WM_KEYDOWN:
                if (lParam AT_BIT(30)) // trying to repeat
                    rp_count++;

                events->Enqueue(new Events::KeyPressedEvent(wParam, rp_count));
                break;
            case WM_KEYUP: 
                rp_count = 0;
                events->Enqueue(new Events::KeyReleasedEvent(wParam));
                break;
#pragma endregion

            default:
                return DefWindowProc(_hWnd, uMsg, wParam, lParam);
                break;
        }
    }

    std::optional<int> Window::ProcessMessages()
    {
        MSG msg;
        ZeroMemory(&msg, sizeof(MSG));

        // while the message queue has something in it
        // process messages.. but do NOT block on empty queue
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                return msg.wParam;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return {};
    }

    bool Window::InitEventsQueue(DataStructures::Queue<Events::Event*>& queue)
    {
        events = &queue;
        return events == nullptr ? false : true;
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