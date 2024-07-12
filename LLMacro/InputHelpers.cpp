#include "InputHelpers.hpp"

const char* GetKeyboardKeyString(DWORD vkCode) {

	switch (vkCode)
	{
	case VK_TAB: return "TAB";
	case VK_LEFT: return "Left arrow";
	case VK_RIGHT: return "Right arrow";
	case VK_UP: return "Up arrow";
	case VK_DOWN: return "Down arrow";
	case VK_PRIOR: return "Page Up";
	case VK_NEXT: return "Page Down";
	case VK_HOME: return "Home";
	case VK_END: return "End";
	case VK_INSERT: return "Insert";
	case VK_DELETE: return "Delete";
	case VK_BACK: return "Backspace";
	case VK_SPACE: return "Space";
	case VK_RETURN: return "Enter";
	case VK_ESCAPE: return "Escape";
	case VK_OEM_7: return "Apostrophe";
	case VK_OEM_COMMA: return "Comma";
	case VK_OEM_MINUS: return "Minus";
	case VK_OEM_PERIOD: return "Period";
	case VK_OEM_2: return "Slash";
	case VK_OEM_1: return "Semicolon";
	case VK_OEM_PLUS: return "Equal";
	case VK_OEM_4: return "Left bracket";
	case VK_OEM_5: return "Backslash";
	case VK_OEM_6: return "Right bracket";
	case VK_OEM_3: return "Grave accent";
	case VK_CAPITAL: return "Caps Lock";
	case VK_SCROLL: return "Scroll Lock";
	case VK_NUMLOCK: return "Num Lock";
	case VK_SNAPSHOT: return "Print Screen";
	case VK_PAUSE: return "Pause";
	case VK_NUMPAD0: return "NUM0";
	case VK_NUMPAD1: return "NUM1";
	case VK_NUMPAD2: return "NUM2";
	case VK_NUMPAD3: return "NUM3";
	case VK_NUMPAD4: return "NUM4";
	case VK_NUMPAD5: return "NUM5";
	case VK_NUMPAD6: return "NUM6";
	case VK_NUMPAD7: return "NUM7";
	case VK_NUMPAD8: return "NUM8";
	case VK_NUMPAD9: return "NUM9";
	case VK_DECIMAL: return "Decimal";
	case VK_DIVIDE: return "Divide";
	case VK_MULTIPLY: return "Multiply";
	case VK_SUBTRACT: return "Subtract";
	case VK_ADD: return "Add";
		//case IM_VK_KEYPAD_ENTER: return "Keypad Enter";
	case VK_LSHIFT: return "Left Shift";
	case VK_LCONTROL: return "Left Ctrl";
	case VK_LMENU: return "Left Alt";
	case VK_LWIN: return "Left Super";
	case VK_RSHIFT: return "Right Shift";
	case VK_RCONTROL: return "Right Ctrl";
	case VK_RMENU: return "Right Alt";
	case VK_RWIN: return "Right Super";
	case VK_APPS: return "Menu";
	case '0': return "0";
	case '1': return "1";
	case '2': return "2";
	case '3': return "3";
	case '4': return "4";
	case '5': return "5";
	case '6': return "6";
	case '7': return "7";
	case '8': return "8";
	case '9': return "9";
	case 'A': return "A";
	case 'B': return "B";
	case 'C': return "C";
	case 'D': return "D";
	case 'E': return "E";
	case 'F': return "F";
	case 'G': return "G";
	case 'H': return "H";
	case 'I': return "I";
	case 'J': return "J";
	case 'K': return "K";
	case 'L': return "L";
	case 'M': return "M";
	case 'N': return "N";
	case 'O': return "O";
	case 'P': return "P";
	case 'Q': return "Q";
	case 'R': return "R";
	case 'S': return "S";
	case 'T': return "T";
	case 'U': return "U";
	case 'V': return "V";
	case 'W': return "W";
	case 'X': return "X";
	case 'Y': return "Y";
	case 'Z': return "Z";
	case VK_F1: return "F1";
	case VK_F2: return "F2";
	case VK_F3: return "F3";
	case VK_F4: return "F4";
	case VK_F5: return "F5";
	case VK_F6: return "F6";
	case VK_F7: return "F7";
	case VK_F8: return "F8";
	case VK_F9: return "F9";
	case VK_F10: return "F10";
	case VK_F11: return "F11";
	case VK_F12: return "F12";
	case VK_F13: return "F13";
	case VK_F14: return "F14";
	case VK_F15: return "F15";
	case VK_F16: return "F16";
	case VK_F17: return "F17";
	case VK_F18: return "F18";
	case VK_F19: return "F19";
	case VK_F20: return "F20";
	case VK_F21: return "F21";
	case VK_F22: return "F22";
	case VK_F23: return "F23";
	case VK_F24: return "F24";
	case VK_BROWSER_BACK: return "App Back";
	case VK_BROWSER_FORWARD: return "App Forward";
	default: return "KUnkown";
	}
}

const char* GetMouseKeyString(DWORD wParam, DWORD mouseData, int& state) {
	switch (wParam) {
	case WM_MOUSEMOVE: state = NULL; return "Move";
	case WM_LBUTTONDOWN: state = down; return "LButton";
	case WM_LBUTTONUP: state = up; return "LButton";
	case WM_RBUTTONDOWN: state = down; return "RButton";
	case WM_RBUTTONUP: state = up; return "RButton";
	case WM_XBUTTONDOWN: state = down; // It seems like mouseData is not null only if there's an XBUTTON event
		if (mouseData == 0x20000)
		return "M4Button";
					   else if (mouseData == 0x10000)
		return "M5Button";
	case WM_XBUTTONUP: 
		state = up;
		if(mouseData == 0x20000)
			return "M4Button";
		else if (mouseData == 0x10000)
			return "M5Button";

	default: return "MUnkown";
	}
}
