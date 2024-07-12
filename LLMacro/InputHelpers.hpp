#pragma once
#include <Windows.h>

enum keyStates {
	 down = 1,
	 up = 2 
};

const char* GetMouseKeyString(DWORD wParam, DWORD mouseData, int& state);
const char* GetKeyboardKeyString(DWORD vkCode);