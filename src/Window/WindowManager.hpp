#ifndef J3_WINDOWMANAGER_H
#define J3_WINDOWMANAGER_H

#include <stdio.h>

#include "Window.hpp"

namespace J3 
{
	class WindowManager 
	{
		public:
			static size_t getWindowCount();
			//static Window* getWindow(size_t id);
	};
}

#endif // J3_WINDOWMANAGER_H