#pragma once

#include "../Core.h"

#include "BaseWindow.h"
#include <optional>

#include "../../data_structures/Queue.h"

#include "../Input/Keyboard.h"
#include "../Input/Mouse.h"

#include "../Events/Event.h"
#include "../Events/KeyEvents.h"
#include "../Events/MouseEvents.h"

namespace ShadowEngine {

	class SHADOW_API Window : public BaseWindow<Window> {
	public:
		virtual BOOL Create(PCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle = 0, int x = 0, int y = 0, int nWidth = 1280, int nHeight = 720, HWND hWndParent = 0, HMENU hMenu = 0) override;
		virtual PCWSTR ClassName() const override;
		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
		
		static std::optional<int> ProcessMessages();

		bool InitEventsQueue(DataStructures::Queue<Events::Event*>& queue);
		bool InitKeyboard(Input::Keyboard& kb);
		bool InitMouse(Input::Mouse& mo);

		RECT GetWindowSize();
		RECT GetClientSize();

	private:
		RECT windowRect = {0};
		RECT clientRect = {0};

		// ptr to the applications event queue so we can populate it with WMessges
		DataStructures::Queue<Events::Event*>* events;

		// ptr to the applications keyboard so that we can track the keyboard states clientside
		Input::Keyboard* keyboard;
		Input::Mouse* mouse;
	};
}