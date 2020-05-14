#include "InputManager.h"

Keyboard* InputManager::keyboards[] = {new Keyboard()};

bool* InputManager::registerKeyboardEvent(const char* name, KCode_t keycode)
{
    return NULL;
}

bool* InputManager::registerKeyboardEvent(const char* name, KCode_t keycode, Keyboard& device)
{
    return NULL;
}