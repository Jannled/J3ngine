/**
 * \file Window.h
 * \author Jannled
 * \brief Header for a minimal application-window that creates an OpenGL context for Windows and Linux.
 */

#ifndef J3_GLWINDOW_H
#define J3_GLWINDOW_H

#include "Window/Platform.h"

#ifndef J3_GL_MAJOR
#define J3_GL_MAJOR 3
#endif

#ifndef J3_GL_MINOR
#define J3_GL_MINOR 3
#endif

#include "J3KeyCodes.h"

#include "Galogen46.h"

namespace J3Window
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
	bool keyboardListener(KCode_t key);

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

#endif