/**
 * \file GLWindow.h
 * \author Jannled
 * \brief Header for a minimal application-window that creates an OpenGL context for Windows and Linux.
 */

#ifndef JGLWINDOW_H
#define JGLWINDOW_H

//Windows
#ifdef _WIN32
#define OS_Windows

// Linux
#elif __linux__
#define OS_Linux
#endif

#include <stdbool.h>
#include "lib/Galogen46.h"

namespace GLWindow
{
	typedef struct {
		int x, y;
	} Point;

	void pre(int argc, char **argv);
	bool init();
	bool update(float delta);
	void quit();
	void resize(int width, int height);

	bool show(const char *title, int width, int height);
	Point getSize();
	Point getPosition();

	void setSize(int width, int height);
	void setTitle(const char *title);
	
	void cursorListener(int movex, int movey);

	long getMilliseconds();

	Point getCursorPos();
	void showCursor(bool visible);

	void MessageCallback(
				GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam
	);
}

#endif //JGLWINDOW_H