#ifndef J3_WINDOW_H
#define J3_WINDOW_H

#ifndef J3_GL_MAJOR
#define J3_GL_MAJOR 3
#endif

#ifndef J3_GL_MINOR
#define J3_GL_MINOR 3
#endif

#include "J3KeyCodes.h"

namespace J3
{
	typedef struct {
		unsigned int x, y;
	} Vec2D;

	class Window
	{
		public:
			Window();
			~Window();

			void setTitle(const char* title);
			void resize(unsigned int width, unsigned int height);
			void resize(Vec2D dimension);
			void showCursor(bool show);
			void fullscreen(bool fullscreen);
	};
}

void mainJ3(int argc, char** argv);

#endif // J3_WINDOW_H