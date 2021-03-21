#pragma once

#include "../Core.h"

#include "BaseWindow.h"
#include <optional>

#include "../Input/Keyboard.h"
#include "../Input/Mouse.h"

#include "../../data_structures/Queue.h"

#include "../Events/Event.h"
#include "../Events/KeyEvents.h"
#include "../Events/MouseEvents.h"
#include "../Graphics2D/Graphics2D.h"

namespace ShadowEngine {

	class SHADOW_API Window : public BaseWindow<Window> {
	public:
		virtual BOOL Create(PCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle = 0, int x = 0, int y = 0, int nWidth = 1280, int nHeight = 720, HWND hWndParent = 0, HMENU hMenu = 0) override;
		virtual PCWSTR ClassName() const override;
		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		static std::optional<int> ProcessMessages();

		RECT GetWindowSize();
		RECT GetClientSize();

		DataStructures::Queue<Events::Event*> GetEvents();


		Input::Keyboard GetKeyboard();
		Input::Mouse GetMouse();

	

	private:

		Graphics2D gfx;

		Input::Keyboard keyboard;
		Input::Mouse mouse;

		DataStructures::Queue<Events::Event*> _events;

		RECT windowRect = {0};
		RECT clientRect = {0};

	};
}