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

namespace GLWindow
{
	void pre();
	bool init();
	bool update(float delta);
	void quit();
	void resize(int width, int height);

	bool show(const char *title, int width, int height);
	int getWidth();
	int getHeight();

	void setSize(int width, int height);
	void setTitle(const char *title);
}

#endif //JGLWINDOW_H