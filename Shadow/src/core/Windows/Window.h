#include "../Core.h"
#include "BaseWindow.h"

namespace ShadowEngine {

	class SHADOW_API Window : public BaseWindow<Window> {
	public:
		virtual BOOL Create(PCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle = 0, int x = 0, int y = 0, int nWidth = 1280, int nHeight = 720, HWND hWndParent = 0, HMENU hMenu = 0) override;
		virtual PCWSTR ClassName() const override;
		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		RECT GetWindowSize();
		RECT GetClientSize();

	private:
		RECT windowRect = {0};
		RECT clientRect = {0};
	};
}