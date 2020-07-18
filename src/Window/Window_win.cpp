#include "Window/Platform.h"
#ifdef OS_WINDOWS

#include "Window.hpp"

using namespace J3;

Window::Window()
{

}

void Window::setTitle(const char* title)
{

}

void Window::resize(unsigned int width, unsigned int height)
{

}

void Window::resize(Vec2D dimension)
{
	
}

void Window::showCursor(bool show)
{
    
}
void Window::fullscreen(bool fullscreen)
{

}

Window::~Window()
{

}

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd_line, int pshow)
{
	_inst = &inst;
	_prev = &prev;
	_cmd_line = &cmd_line;
	_show = &pshow;


	//Convert to int argc, char** argv
	int argc;
    LPWSTR *szArglist = CommandLineToArgvW(GetCommandLineW(), &argc);
    char **argv = new char*[argc];
    for (int i=0; i<argc; i++) {
        int lgth = wcslen(szArglist[i]);
        argv[i] = new char[lgth+1];
        for (int j=0; j<=lgth; j++)
            argv[i][j] = char(szArglist[i][j]);
    }
    LocalFree(szArglist);

	mainJ3(argc, argv);

	return 0;
}

#endif