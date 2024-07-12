# About
Lightweight macro recorder and player that uses low level mouse &amp; keyboard hooks to get the most accurate inputs.

# Why
I chose to make an open-source macro recorder for better portability and implementation because the only open-source macro recorder I found was Autohotkey and it's not meant for portability.

# Running & Implementation
Binary will prompt you with a CMD at startup showing the controls.

```
Controls: F1 - Start/Stop recording
          F2 - Start/Stop playback
          F3 - Print events vector
```
Implementing:
1. Add the files (CPP & HPP) in your project.
2. Add the following library `#include "Hooks.hpp`
3. Make sure your process is aware of DPI by using `SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE)` otherwise mouse inputs won't be accurate if the monitor scale is other than 100%
4. Make sure your thread is receiving messages ( `GetMessage(nullptr, nullptr, 0, 0)` )
5. Start a new hookingThread to avoid input lag
I did it like this while the main thread is receiving messages:
```
	std::thread hThread(hookingThread);
	hThread.detach();
```

# Build informaation
Code editor: `Visual Studio 2022`

Configurations:

- `Release`: no console logs

- `Debug`: console logs

# Licenese
This project is licensed under the MIT License.
