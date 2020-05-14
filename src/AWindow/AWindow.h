/**
 * \file AWindow.h
 * \author Jannled
 * \brief Header for a minimal application-window that creates an OpenGL context for Windows and Linux.
 */

#ifndef JGLWINDOW_H
#define JGLWINDOW_H

//Windows __MINGW32__
#if defined _WIN32 || defined __MINGW32__
#define OS_Windows
#endif

// Linux
#ifdef __linux__
#define OS_Linux
#endif

#ifndef JGL_MAJOR
#define JGL_MAJOR 3
#endif

#ifndef JGL_MINOR
#define JGL_MINOR 3
#endif

#include "JKeyCodes.h"

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

	void setKeymap(unsigned int key, unsigned int pos);
	void printKeymap();

	const char keyNames[JKEY_NUM][JKEY_NAME] = {
		"ESC", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
		"CIRC", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "?", "'", "BACKSPACE",
		"TAB", "Q", "W", "E", "R", "T", "Z", "U", "I", "O", "P", "Ü", "+", "ENTER",
		"CAPSLOCK", "A", "S", "D", "F", "G", "H", "J", "K", "L", "Ö", "Ä", "#",
		"L SHIFT", "<", "Y", "X", "C", "V", "B", "N", "M", ",", ".", "-", "R SHIFT",
		"L CTRL", "L ALT", "SPACEBAR", "ALT CTRL", "Context", "R CTRL",
		"SCROLL", "PAUSE", "PASTE", "POS1", "DEL", "END", "BILD UP", "BILD DOWN",
		"LEFT", "RIGHT", "UP", "DOWN",
		"NUMLOCK", "NUM *", "NUM /", "NUM +", "NUM -", "NUM ENTER", "NUM ,", 
		"NUM 1", "NUM 2", "NUM 3", "NUM 4", "NUM 5", "NUM 6", "NUM 7", "NUM 8", "NUM 9", "NUM 0"
	};
}

#endif //JGLWINDOW_H