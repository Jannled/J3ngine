#ifndef J3_WINDOW_H
#define J3_WINDOW_H

#ifndef J3_GL_MAJOR
#define J3_GL_MAJOR 3
#endif

#ifndef J3_GL_MINOR
#define J3_GL_MINOR 3
#endif

#include "Window/Platform.h"

#include "Galogen46.h"

#include "J3KeyCodes.h"

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

namespace J3
{
	typedef struct {
		unsigned int x, y;
	} Vec2D;

	class Window
	{
		public:
			Window(char* title, unsigned int width = 1280, unsigned int height = 720);
			~Window();

			void setTitle(const char* title);
			void resize(unsigned int width, unsigned int height);
			void resize(Vec2D dimension);
			void showCursor(bool show);
			void fullscreen(bool fullscreen);

			static long getMilliseconds();
			static void messageBox(const char *msg);

			static void MessageCallback(
				GLenum source,
				GLenum type,
				GLuint id,
				GLenum severity,
				GLsizei length,
				const GLchar* message,
				const void* userParam
			);

		private:
			void show(const char* title, unsigned int width, unsigned int height);
			char* title;
			unsigned int width, height;
	};
}

int mainJ3(int argc, char** argv);

#endif // J3_WINDOW_H