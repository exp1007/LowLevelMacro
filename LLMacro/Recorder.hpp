#pragma once
#include <vector>

extern bool recording;
extern bool playing;

enum eventType { Mouse, Keyboard};

//struct inputData {
//
//	bool type; // 0 - Mouse, 1 - Keyboard
//
//	// Global
//	DWORD input; // This is used for both vkKeys and mouse inputs
//	DWORD time;
//	int state;
//
//	// Mouse specific
//	DWORD mouseData;
//	POINT pt;
//};

class EventData {
public:
	bool eventType;

	DWORD input; // This is used for both vkKeys and mouse inputs
	DWORD time;
	int state;

	// Constructor
	EventData(bool type, DWORD input, DWORD time, int state)
		: eventType(type), input(input), time(time), state(state) {}

	// Virtual destructor to ensure proper cleanup
	virtual ~EventData() {}
};

class MouseEvent : public EventData {
public:
	DWORD mouseData;
	POINT pt;

	// Constructor
	MouseEvent(bool eventType, DWORD input, DWORD time, int state, DWORD mouseData, POINT pt)
		: EventData(eventType, input, time, state), mouseData(mouseData), pt(pt) {}

	// Destructor
	~MouseEvent() {}
};

class KeyboardEvent : public EventData {
public:
	// Constructor
	KeyboardEvent(bool eventType, DWORD input, DWORD time, int state)
		: EventData(eventType, input, time, state) {}

	// Destructor
	~KeyboardEvent() {}
};

void addEvent(std::unique_ptr<MouseEvent, std::default_delete<MouseEvent>>& input);
void addEvent(std::unique_ptr<KeyboardEvent, std::default_delete<KeyboardEvent>>& input);
void printInputVectors();

void startRecord();

void play();
