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
        
        RECT desired = { 0,0,nWidth, nHeight };
        AdjustWindowRectEx(&desired, dwStyle, hMenu == nullptr ? false : true, dwExStyle);
        UINT new_width = desired.right - desired.left;
        UINT new_height = desired.bottom - desired.top;

        _hWnd = CreateWindowEx(
            dwExStyle, 
            ClassName(), 
            lpWindowName, 
            dwStyle, 
            x, 
            y,
            new_width, 
            new_height,
            hWndParent, 
            hMenu, 
            GetModuleHandle(NULL),
            this
        );
        
        if (_hWnd == NULL) {

            SH_DEBUGGER_ERR("HWND IS NULL");
            return false;

        }

        if (!gfx.Init(_hWnd)) {
            SH_DEBUGGER_ERR("COULD NOT INITILIZE GRAPHICS DISPLAY");
            return false;
        }

        GetClientRect(_hWnd, &clientRect);
        GetWindowRect(_hWnd, &windowRect);


        return true;
    }

    PCWSTR Window::ClassName() const
    {
        return L"WINDOW";
    }


    DataStructures::Queue<Events::Event*> Window::GetEvents() {
        return _events;
    }

    Input::Keyboard Window::GetKeyboard()
    {
        return keyboard;
    }

    Input::Mouse Window::GetMouse()
    {
        return mouse;
    }


    LRESULT Window::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        static int rp_count = 0;
        Window* win = reinterpret_cast<Window*>(static_cast<LONG_PTR>(GetWindowLongPtrW(_hWnd, GWLP_USERDATA)));
        LRESULT res = 0;
        if (win) {

            switch (uMsg) {

                case WM_DESTROY:
                    PostQuitMessage(0);
                    res = 1;
                    break;

                #pragma region RENDER MESSAGES
                case WM_SIZE:
                    gfx.OnResize(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                    break;

                case WM_PAINT:
                    {
                        gfx.Render(_hWnd);
                        ValidateRect(_hWnd, nullptr);
                    }
                    res = 0;
                    break;

                case WM_DISPLAYCHANGE:
                   InvalidateRect(_hWnd, nullptr, FALSE);
                   break;

                #pragma endregion

                 #pragma region MOUSE INPUT MESSAGES

                case WM_MOUSEMOVE:
                    win->_events.Enqueue(new Events::MouseMovedEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
                    win->mouse.Position({ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) });
                    break;

                case WM_LBUTTONDOWN:
                    win->_events.Enqueue(new Events::MouseClickEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), Events::MOUSE_BUTTON::LEFT));
                    win->mouse.buttons[0] = true;
                    break;

                case WM_MBUTTONDOWN:
                    win->_events.Enqueue(new Events::MouseClickEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), Events::MOUSE_BUTTON::MIDDLE));
                    win->mouse.buttons[1] = true;
                    break;

                case WM_RBUTTONDOWN:
                    win->_events.Enqueue(new Events::MouseClickEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), Events::MOUSE_BUTTON::RIGHT));
                    win->mouse.buttons[2] = true;
                    break;


                case WM_LBUTTONUP:
                    win->_events.Enqueue(new Events::MouseReleasedEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), Events::MOUSE_BUTTON::LEFT));
                    win->mouse.buttons[0] = false;
                    break;

                case WM_MBUTTONUP:
                    win->_events.Enqueue(new Events::MouseReleasedEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), Events::MOUSE_BUTTON::MIDDLE));
                    win->mouse.buttons[1] = false;
                    break;

                case WM_RBUTTONUP:
                    win->_events.Enqueue(new Events::MouseReleasedEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), Events::MOUSE_BUTTON::RIGHT));
                    win->mouse.buttons[2] = false;
                    break;

                 #pragma endregion

                 #pragma region KEYBOARD INPUT MESSAGES
                case WM_KEYDOWN:
                    if (lParam AT_BIT(30)) // trying to repeat
                        rp_count++;
                    win->_events.Enqueue(new Events::KeyPressedEvent(wParam, rp_count));
                    win->keyboard.keystates[wParam] = true;
                    break;
                case WM_KEYUP: 
                    rp_count = 0;
                    win->_events.Enqueue(new Events::KeyReleasedEvent(wParam));
                    win->keyboard.keystates[wParam] = false;
                    break;
                #pragma endregion

                default:
                    res = DefWindowProc(_hWnd, uMsg, wParam, lParam);
                    break;
            }
        }

        return res;
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


    RECT Window::GetWindowSize()
    {
        return windowRect;
    }

    RECT Window::GetClientSize()
    {
        return clientRect;
    }

}