/**
 * \file GLWindow_win.cpp
 * \author Jannled
 * \brief Windows implementation for a simple OpenGL window
 * 
 * Thanks to Nick Rolfe: https://gist.github.com/nickrolfe/1127313ed1dbf80254b614a721b3ee9c
 */

#include "AWindow.h"

#define OS_WINDOWS //REMOVE

#ifdef OS_Windows

// Sample code showing how to create a modern OpenGL window and rendering context on Win32.
// Thanks to nickrolfe: https://gist.github.com/nickrolfe/1127313ed1dbf80254b614a721b3ee9c
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <shellapi.h>

#include "lib/Galogen46.h"

typedef HGLRC WINAPI wglCreateContextAttribsARB_type(HDC hdc, HGLRC hShareContext, const int *attribList);
wglCreateContextAttribsARB_type *wglCreateContextAttribsARB;

// See https://www.opengl.org/registry/specs/ARB/wgl_create_context.txt for all values
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001

typedef BOOL WINAPI wglChoosePixelFormatARB_type(HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
wglChoosePixelFormatARB_type *wglChoosePixelFormatARB;

// See https://www.opengl.org/registry/specs/ARB/wgl_pixel_format.txt for all values
#define WGL_DRAW_TO_WINDOW_ARB 0x2001
#define WGL_ACCELERATION_ARB 0x2003
#define WGL_SUPPORT_OPENGL_ARB 0x2010
#define WGL_DOUBLE_BUFFER_ARB 0x2011
#define WGL_PIXEL_TYPE_ARB 0x2013
#define WGL_COLOR_BITS_ARB 0x2014
#define WGL_DEPTH_BITS_ARB 0x2022
#define WGL_STENCIL_BITS_ARB 0x2023

#define WGL_FULL_ACCELERATION_ARB 0x2027
#define WGL_TYPE_RGBA_ARB 0x202B

//Raw Mouse input
#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC  ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE ((USHORT) 0x02)
#endif
RAWINPUTDEVICE Rid[1];

//Window handles
HINSTANCE *_inst;
HINSTANCE *_prev; 
LPSTR *_cmd_line; 
int *_show;

HWND _window;

static void fatal_error(const char *msg)
{
	MessageBoxA(NULL, msg, "Error", MB_OK | MB_ICONEXCLAMATION);
	exit(EXIT_FAILURE);
}

static void init_opengl_extensions()
{
	// Before we can load extensions, we need a dummy OpenGL context, created using a dummy window.
	// We use a dummy window because you can only set the pixel format for a window once. For the
	// real window, we want to use wglChoosePixelFormatARB (so we can potentially specify options
	// that aren't available in PIXELFORMATDESCRIPTOR), but we can't load and use that before we
	// have a context.
	WNDCLASSA window_class = {
		.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
		.lpfnWndProc = DefWindowProcA,
		.hInstance = GetModuleHandle(0),
		.lpszClassName = "Dummy_WGL_djuasiodwa",
	};

	if (!RegisterClassA(&window_class))
	{
		fatal_error("Failed to register dummy OpenGL window.");
	}

	HWND dummy_window = CreateWindowExA(
		0,
		window_class.lpszClassName,
		"Dummy OpenGL Window",
		0,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,
		0,
		window_class.hInstance,
		0);

	if (!dummy_window)
	{
		fatal_error("Failed to create dummy OpenGL window.");
	}

	HDC dummy_dc = GetDC(dummy_window);

	PIXELFORMATDESCRIPTOR pfd = {
		.nSize = sizeof(pfd),
        .nVersion = 1,
		.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        .iPixelType = PFD_TYPE_RGBA,
        .cColorBits = 32,
        .cAlphaBits = 8,
        .cDepthBits = 24,
        .cStencilBits = 8,
		.iLayerType = PFD_MAIN_PLANE
	};

	int pixel_format = ChoosePixelFormat(dummy_dc, &pfd);
	if (!pixel_format)
	{
		fatal_error("Failed to find a suitable pixel format.");
	}
	if (!SetPixelFormat(dummy_dc, pixel_format, &pfd))
	{
		fatal_error("Failed to set the pixel format.");
	}

	HGLRC dummy_context = wglCreateContext(dummy_dc);
	if (!dummy_context)
	{
		fatal_error("Failed to create a dummy OpenGL rendering context.");
	}

	if (!wglMakeCurrent(dummy_dc, dummy_context))
	{
		fatal_error("Failed to activate dummy OpenGL rendering context.");
	}

	wglCreateContextAttribsARB = (wglCreateContextAttribsARB_type *)wglGetProcAddress(
		"wglCreateContextAttribsARB");
	wglChoosePixelFormatARB = (wglChoosePixelFormatARB_type *)wglGetProcAddress(
		"wglChoosePixelFormatARB");

	wglMakeCurrent(dummy_dc, 0);
	wglDeleteContext(dummy_context);
	ReleaseDC(dummy_window, dummy_dc);
	DestroyWindow(dummy_window);
}

static HGLRC init_opengl(HDC real_dc)
{ 
	init_opengl_extensions();

	// Now we can choose a pixel format the modern way, using wglChoosePixelFormatARB.
	int pixel_format_attribs[] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		0};

	int pixel_format;
	UINT num_formats;
	wglChoosePixelFormatARB(real_dc, pixel_format_attribs, 0, 1, &pixel_format, &num_formats);
	if (!num_formats)
	{
		fatal_error("Failed to set the OpenGL 3.3 pixel format.");
	}

	PIXELFORMATDESCRIPTOR pfd;
	DescribePixelFormat(real_dc, pixel_format, sizeof(pfd), &pfd);
	if (!SetPixelFormat(real_dc, pixel_format, &pfd))
	{
		fatal_error("Failed to set the OpenGL 3.3 pixel format.");
	}

	// Specify that we want to create an OpenGL 3.3 core profile context
	int gl33_attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB,
		3,
		WGL_CONTEXT_MINOR_VERSION_ARB,
		3,
		WGL_CONTEXT_PROFILE_MASK_ARB,
		WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0,
	};

	HGLRC gl33_context = wglCreateContextAttribsARB(real_dc, 0, gl33_attribs);
	if (!gl33_context)
	{
		fatal_error("Failed to create OpenGL 3.3 context.");
	}

	if (!wglMakeCurrent(real_dc, gl33_context))
	{
		fatal_error("Failed to activate OpenGL 3.3 rendering context.");
	}

	return gl33_context;
}

static LRESULT CALLBACK window_callback(HWND window, UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT result = 0;

	switch (msg)
	{
		case WM_INPUT:
		{
			UINT dwSize = 40;
			static BYTE lpb[40];

			GetRawInputData((HRAWINPUT)lparam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

			RAWINPUT* raw = (RAWINPUT*)lpb;

			if (raw->header.dwType == RIM_TYPEMOUSE) 
			{
				int xPosRelative = raw->data.mouse.lLastX;
				int yPosRelative = raw->data.mouse.lLastY;

				GLWindow::cursorListener(xPosRelative, yPosRelative);
			}

			break;
		}

		case WM_SIZE:
			GLWindow::resize(LOWORD(lparam), HIWORD(lparam));
			break;

		case WM_CLOSE:
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			result = DefWindowProcA(window, msg, wparam, lparam);
			break;
	}

	return result;
}

static HWND create_window(HINSTANCE inst, const char* title, int width, int height)
{
	WNDCLASSA window_class = {
		.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
		.lpfnWndProc = window_callback,
		.hInstance = inst,
		.hCursor = LoadCursor(0, IDC_ARROW),
		.hbrBackground = 0,
		.lpszClassName = "WGL_fdjhsklf",
	};

	if (!RegisterClassA(&window_class))
	{
		fatal_error("Failed to register window.");
	}

	// Specify a desired width and height, then adjust the rect so the window's client area will be
	// that size.
	RECT rect = {
		.right = width,
		.bottom = height,
	};
	DWORD window_style = WS_OVERLAPPEDWINDOW;
	AdjustWindowRect(&rect, window_style, false);

	_window = CreateWindowExA(
		0,
		window_class.lpszClassName,
		title,
		window_style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		0,
		0,
		inst,
		0);

	if (!_window)
	{
		fatal_error("Failed to create window.");
	}

	return _window;
}

bool GLWindow::show(const char *title, int width, int height)
{
	HWND window = create_window(*_inst, title, width, height);
	HDC gldc = GetDC(window);
	HGLRC glrc = init_opengl(gldc);

	ShowWindow(window, *_show);

	//Raw Cursor
    Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC; 
    Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE; 
    Rid[0].dwFlags = RIDEV_INPUTSINK;   
    Rid[0].hwndTarget = _window;
    RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));

	UpdateWindow(window);

	//Register error logger
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	std::cout << "GL Renderer: " << glGetString(GL_RENDERER) << "\n";
	std::cout << "GL Version: " << glGetString(GL_VERSION) << "\n";
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

	if(!init())
		return 1;

	double prevTime = getMilliseconds();
	double currentTime = getMilliseconds();
	double deltaTime = 0.0;

	bool running = true;
	while (running)
	{
		MSG msg;
		while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				running = false;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
		}

		currentTime = getMilliseconds();
		deltaTime = double(currentTime - prevTime) * 0.001;
		prevTime = currentTime;

		GLWindow::update(deltaTime);
		SwapBuffers(gldc);
	}

	quit();

	return 0;
}

GLWindow::Point GLWindow::getSize()
{
	Point p;
	RECT rect;
	GetWindowRect(_window, &rect);
	p.x = rect.right - rect.left;
	p.y = rect.bottom - rect.top;
	return p;
}

GLWindow::Point GLWindow::getPosition()
{
	Point p;
	RECT rect;
	GetWindowRect(_window, &rect);
	p.x = rect.left;
	p.y = rect.top;
	return p;
}

GLWindow::Point GLWindow::getCursorPos()
{
	POINT p;
	Point point;
	if(GetCursorPos(&p))
	{
		if(ScreenToClient(_window, &p))
		{
			point.x = p.x;
			point.y = p.y;
			return point;
		}
		else
			fprintf(stderr, "Could not convert screen coordinates to window coordinates!\n");
	}
	else
		fprintf(stderr, "Failed to get cursor position!\n");
	
	point.x = -1;
	point.y = -1;
	return point;
}

void GLWindow::showCursor(bool visible)
{
	ShowCursor(visible);
}

long GLWindow::getMilliseconds()
{
	SYSTEMTIME time;
	GetSystemTime(&time);
	return (((time.wHour * 60 + time.wMinute) * 60 + time.wSecond) * 1000) + time.wMilliseconds;
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

	GLWindow::pre(argc, argv);

	return 0;
}

#endif // OS_Windows