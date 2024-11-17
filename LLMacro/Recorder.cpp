#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>

#include "Recorder.hpp"
#include "Hooks.hpp"
#include "InputHelpers.hpp"
#include "shellscalingapi.h"

bool recording = false;
bool playing = false;


// I know things doesn't look nice but I used unique_ptr to persevere the data when casting to base class
std::vector<std::unique_ptr<EventData>> eventsVec;

void addEvent(std::unique_ptr<MouseEvent, std::default_delete<MouseEvent>>& input) {
	eventsVec.push_back(std::move(input));
}

void addEvent(std::unique_ptr<KeyboardEvent, std::default_delete<KeyboardEvent>>& input) {
	eventsVec.push_back(std::move(input));
}

//void printInputVectors() {
//	std::cout << "Keys:";
//	for (auto it : kInputsVec) {
//		std::cout << "(" << GetKeyboardKeyString(it.vkKey) << " " << (it.state == 1 ? "Down" : "Up") << " " << it.time << ") ";
//	}
//	std::cout << std::endl;
//}

void printInputVectors() {
	std::cout << "Events array:";
	for (const auto& it : eventsVec) {
		if (it->eventType == Mouse) {
			MouseEvent* m = dynamic_cast<MouseEvent*>(it.get());
			std::cout << "(" << GetMouseKeyString(m->input, m->mouseData, m->state) << " " << (it->state == 1 ? "Down" : "Up") << " " << it->time << ") ( " << m->pt.x << " " << m->pt.y << ") ";
		}

		if(it->eventType == Keyboard) {
			KeyboardEvent* m = dynamic_cast<KeyboardEvent*>(it.get()); // Not required rn but may be later
			std::cout << "(" << GetKeyboardKeyString(it->input) << " " << (it->state == 1 ? "Down" : "Up") << " " << it->time << ") ";;
		}
	}
	std::cout << std::endl;
}

void startRecord() {

	if (!recording) {
		eventsVec.clear(); recording = true;
	}
	else recording = false;
}

void playMouseInput(size_t& index) {
	INPUT ip;
	MouseEvent* m = dynamic_cast<MouseEvent*>(eventsVec[index].get());

	// These flags are different, idk why but microsoft
	DWORD dwFlagSelector;
	switch (m->input) {
	case WM_MOUSEMOVE: dwFlagSelector = MOUSEEVENTF_MOVE; break;
	case WM_LBUTTONDOWN: dwFlagSelector = MOUSEEVENTF_LEFTDOWN; break;
	case WM_LBUTTONUP: dwFlagSelector = MOUSEEVENTF_LEFTUP; break;
	case WM_RBUTTONDOWN: dwFlagSelector = MOUSEEVENTF_RIGHTDOWN; break;
	case WM_RBUTTONUP: dwFlagSelector = MOUSEEVENTF_RIGHTUP; break;
	case WM_XBUTTONDOWN: dwFlagSelector = MOUSEEVENTF_XDOWN; break;
	case WM_XBUTTONUP: dwFlagSelector = MOUSEEVENTF_XUP; break;
	default: dwFlagSelector = NULL;
	}

	// This requires SetProcessDpiAwarenessContext otherwise will return the default value (96)
	// Get the DPI for the primary monitor (assuming the primary monitor is the focus)
	HMONITOR primaryMonitor = MonitorFromWindow(GetDesktopWindow(), MONITOR_DEFAULTTOPRIMARY);
	UINT dpiX, dpiY;
	if (GetDpiForMonitor(primaryMonitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY) != S_OK) {
		dpiX = 96;  // Default DPI value if retrieval fails
		dpiY = 96;
	}

	// Get the screen dimensions based on DPI
	int screenX = GetSystemMetricsForDpi(SM_CXSCREEN, dpiX);
	int screenY = GetSystemMetricsForDpi(SM_CYSCREEN, dpiY);

	// Set up a generic mouse event
	ip.mi.dwExtraInfo = 0;
	ip.mi.time = 0;
	ip.type = INPUT_MOUSE;

	// Set up mouse event
	ip.mi.dx = (m->pt.x * 65535) / screenX;
	ip.mi.dy = (m->pt.y * 65535) / screenY;

	if (m->mouseData == 0x20000)
		ip.mi.mouseData = XBUTTON1;
	else if (m->mouseData == 0x10000)
		ip.mi.mouseData = XBUTTON2;

	ip.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | dwFlagSelector | MOUSEEVENTF_MOVE;

	SendInput(1, &ip, sizeof(INPUT));

	// May use some other methods in the future, most likely mouse_event since sendinput is just a wrapper for it
	//mouse_event(ip.mi.dwFlags, inputsVec[index].pt.x, inputsVec[index].pt.y, 0, 0);
	//SetCursorPos(inputsVec[index].pt.x, inputsVec[index].pt.y);

	DWORD delayTime = 0;
	if (index + 1 < eventsVec.size())
		delayTime = eventsVec[index + 1]->time - eventsVec[index]->time;
	else
		delayTime = 0;

	std::this_thread::sleep_for(std::chrono::milliseconds(delayTime));

	return;
}

void playKeyboardInput(size_t& index) {
	INPUT ip;

	// Set up a generic keyboard event
	//ip.type = INPUT_KEYBOARD;
	//ip.ki.wScan = 0; // Hardware scan code for key , null if we use vk key
	//ip.ki.time = 0;
	//ip.ki.dwExtraInfo = 0;

	//// // Set up keyboard event
	//ip.ki.wVk = eventsVec[index]->input;
	//ip.ki.dwFlags = eventsVec[index]->state;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wVk = 0;
	
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// // Set up keyboard event
	ip.ki.wScan = eventsVec[index]->input;
	ip.ki.dwFlags = eventsVec[index]->state;

	SendInput(1, &ip, sizeof(INPUT));

	DWORD delayTime = 0;

	if (index + 1 < eventsVec.size())
		delayTime = eventsVec[index + 1]->time - eventsVec[index]->time;
	else
		delayTime = 0;

	std::this_thread::sleep_for(std::chrono::milliseconds(delayTime));

	return;
}

void playThread() {

	while (playing == true) {
		std::cout << "Playback started" << std::endl;

		for (size_t index = 0; index < eventsVec.size(); index++) {
			if (playing == false)
				return;

			if (eventsVec[index]->eventType == false)
				playMouseInput(index);
			else
				playKeyboardInput(index);
		}
		
		std::cout << "Playback finished" << std::endl;
	}


#ifdef _DEBUG
	std::cout << "Playback finished" << std::endl;
#endif

	return;
}

void play() {
	recording = false;
	
	std::thread playTh(playThread);
	playTh.detach();
}
