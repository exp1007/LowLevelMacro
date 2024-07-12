#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>

#include "Recorder.hpp"
#include "Hooks.hpp"

// IOManager 
// Author exp
// Version 1.0

int main() {

	// Getting the actual screen size requires a DPI aware process
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);

	// Using a new thread to avoid lag input
	std::thread hThread(hookingThread);
	hThread.detach();

	// Main loop
	while (true)
	{
		GetMessage(nullptr, nullptr, 0, 0);
	}

	return 0;
}