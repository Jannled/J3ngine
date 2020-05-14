#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "HID.h"
#include "Keyboard.h"

class InputManager
{
	public:
		static Keyboard* keyboards[];

		static bool* registerKeyboardEvent(const char* name, KCode_t keycode);
		static bool* registerKeyboardEvent(const char* name, KCode_t keycode, Keyboard& device);
};

#endif // INPUTMANAGER_H