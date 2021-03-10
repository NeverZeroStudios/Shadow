#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace ShadowEngine {
    template<class _DERIVED_>
    class BaseWindow {
    public:
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            _DERIVED_* pThis = NULL;

            if (uMsg == WM_NCCREATE)
            {
                CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
                pThis = (_DERIVED_*)pCreate->lpCreateParams;
                SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

                pThis->_hWnd = hwnd;
            }
            else
            {
                pThis = (_DERIVED_*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
            }
            if (pThis)
            {
                return pThis->HandleMessage(uMsg, wParam, lParam);
            }
            else
            {
                return DefWindowProc(hwnd, uMsg, wParam, lParam);
            }
        }

        BaseWindow() : _hWnd(NULL) { }

        /*  1. Window Name  PCWSTR {REQ}
            2. Style        DWORD  {REQ}
            3. ExStyle      DWORD
            4. X            int
            5. Y            int
            6. Width        int
            7. Height       int
            8. Parent       HWND
            9. Menu         HMENU */
        virtual BOOL Create( PCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle = 0, int x = 0, int y = 0, int nWidth = 1280, int nHeight = 720, HWND hWndParent = 0, HMENU hMenu = 0 )
        {
            WNDCLASS wc = { 0 };

            wc.lpfnWndProc = _DERIVED_::WindowProc;
            wc.hInstance = GetModuleHandle(NULL);
            wc.lpszClassName = ClassName();

            RegisterClass(&wc);

            _hWnd = CreateWindowEx(
                dwExStyle, ClassName(), lpWindowName, dwStyle, x, y,
                nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this
            );

            return (_hWnd ? TRUE : FALSE);
        }

        HWND GetWindow() const { return _hWnd; }

    protected:

        virtual PCWSTR  ClassName() const = 0;
        virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

        HWND _hWnd;
    };

}