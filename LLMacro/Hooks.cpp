#include <Windows.h>
#include <iostream>

#include "InputHelpers.hpp"
#include "Recorder.hpp"

HHOOK _keyhook;
HHOOK _mousehook;
MSLLHOOKSTRUCT mouseStruct;
KBDLLHOOKSTRUCT kbdStruct;

LRESULT __stdcall KeyboardHookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0)
	{
		if (wParam)
		{
			// Check if key is up or down
			int state = 0;
			if (wParam == WM_KEYDOWN)
				state = 1;
			if (wParam == WM_KEYUP)
				state = 2;

			kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);

			if (kbdStruct.vkCode == VK_F1 && state == 1) {
				startRecord();
				return CallNextHookEx(_keyhook, nCode, wParam, lParam);
			}

			if (kbdStruct.vkCode == VK_F2 && state == 1) {
				play();
				return CallNextHookEx(_keyhook, nCode, wParam, lParam);
			}

			if (kbdStruct.vkCode == VK_F3 && state == 1) {
				printInputVectors();
				return CallNextHookEx(_keyhook, nCode, wParam, lParam);
			}

			if (kbdStruct.vkCode && recording)
			{
				auto k = std::make_unique<KeyboardEvent>(Keyboard, kbdStruct.vkCode, kbdStruct.time, state);
				addEvent(k);

#ifdef _DEBUG
				std::cout << "[Keyboard-Hook] " << GetKeyboardKeyString(kbdStruct.vkCode) << " (" << (state == 1 ? "Down" : "Up") << ")" << std::endl;
#endif
			}
		}
	}
	return CallNextHookEx(_keyhook, nCode, wParam, lParam);
}

LRESULT __stdcall MouseHookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	if(!recording)
		return CallNextHookEx(_mousehook, nCode, wParam, lParam);

	if (nCode >= 0)
	{
		if (wParam) {
			mouseStruct = *((tagMSLLHOOKSTRUCT*)lParam);

			int state = 0;
			const char* action = GetMouseKeyString(wParam, mouseStruct.mouseData, state);

			auto m = std::make_unique<MouseEvent>(Mouse, wParam, mouseStruct.time, state, mouseStruct.mouseData, mouseStruct.pt);
			addEvent(m);

#ifdef _DEBUG
			if (strcmp(action, "Move"))
				std::cout << "[Mouse-Hook] " << action << " (" << (state == 1 ? "Down" : "Up") << ")" << " - (" << mouseStruct.pt.x << " " << mouseStruct.pt.y << ")" << std::endl;
			else
				std::cout << "[Mouse-Hook] " << "Move" << " (" << mouseStruct.pt.x << " " << mouseStruct.pt.y << ")" << std::endl;
#endif

		}
	}
	return CallNextHookEx(_mousehook, nCode, wParam, lParam);
}

void hookingThread()
{
		_mousehook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookCallback, NULL, 0);

		if (_mousehook == NULL)
			std::cout << "[Hooks] " << "Failed to install Mouse hook.\n";
		else
			std::cout << "[Hooks] " << "Installed Mouse hook.\n";

		_keyhook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookCallback, NULL, 0);

		if (_keyhook == NULL)
			std::cout << "[Hooks] " << "Failed to install Keyboard hook.\n";
		else
			std::cout << "[Hooks] " << "Installed Keyboard hook.\n" << std::endl;

		std::cout << "Controls: F1 - Start/Stop recording" << std::endl;
		std::cout << "          F2 - Start/Stop playback" << std::endl;
		std::cout << "          F3 - Print events vector" << std::endl << std::endl;

		GetMessage(nullptr, nullptr, 0, 0);
}

//void SetHook(int hookID)
//{
//	if (hookID == WH_MOUSE_LL) {
//		if (!(_mousehook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookCallback, NULL, 0)))
//			std::cout << "[Hooks] " << "Failed to install hook.\n";
//		else
//			std::cout << "[Hooks] " << "Installed Mouse hook.\n";
//
//	}
//	else if (hookID == WH_KEYBOARD_LL) {
//		if (!(_keyhook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookCallback, NULL, 0)))
//			std::cout << "[Hooks] " << "Failed to install hook.\n";
//		else
//			std::cout << "[Hooks] " << "Installed Keyboard hook.\n";
//	}
//
//	GetMessage(nullptr, nullptr, 0, 0); //make the thread not close
//}