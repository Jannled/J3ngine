/**
 * \file GLWindow_x11.cpp
 * \author Jannled
 * \brief Linux implementation for a simple OpenGL window
 * 
 * Thanks to gamedevtech: https://github.com/gamedevtech/X11OpenGLWindow
 */

#include "AWindow.h"

#ifdef OS_Linux

using namespace GLWindow;
// g++ -o X11Window X11.cpp -lX11 -lGL -lGLEW -L/usr/X11/lib -I/opt/X11/include
#include <iostream>
#include <cstring>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>

#include <GL/gl.h>
#include <GL/glx.h>

#include <sys/time.h>
#include <unistd.h>

#define FPS 30
#define TEST_LOCAL

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

#define SKIP_TICKS      (1000 / FPS)

Display* display;
Window window;
Screen* screen;
int screenId;
XEvent ev;

static bool isExtensionSupported(const char *extList, const char *extension) {
	return strstr(extList, extension) != 0;
}

bool GLWindow::show(const char *title, int width, int height) 
{
	// Open the display
	display = XOpenDisplay(NULL);
	if (display == NULL) {
		std::cout << "Could not open display\n";
		return 1;
	}
	screen = DefaultScreenOfDisplay(display);
	screenId = DefaultScreen(display);
	
	// Check GLX version
	GLint majorGLX, minorGLX = 0;
	glXQueryVersion(display, &majorGLX, &minorGLX);
	if (majorGLX <= 1 && minorGLX < 2) {
		std::cout << "GLX 1.2 or greater is required.\n";
		XCloseDisplay(display);
		return 1;
	}

	GLint glxAttribs[] = {
		GLX_X_RENDERABLE    , True,
		GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
		GLX_RENDER_TYPE     , GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
		GLX_RED_SIZE        , 8,
		GLX_GREEN_SIZE      , 8,
		GLX_BLUE_SIZE       , 8,
		GLX_ALPHA_SIZE      , 8,
		GLX_DEPTH_SIZE      , 24,
		GLX_STENCIL_SIZE    , 8,
		GLX_DOUBLEBUFFER    , True,
		None
	};
	
	int fbcount;
	GLXFBConfig* fbc = glXChooseFBConfig(display, screenId, glxAttribs, &fbcount);
	if (fbc == 0) {
		std::cout << "Failed to retrieve framebuffer.\n";
		XCloseDisplay(display);
		return 1;
	}

	// Pick the FB config/visual with the most samples per pixel
	int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;
	for (int i = 0; i < fbcount; ++i) {
		XVisualInfo *vi = glXGetVisualFromFBConfig( display, fbc[i] );
		if ( vi != 0) {
			int samp_buf, samples;
			glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf );
			glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLES       , &samples  );

			if ( best_fbc < 0 || (samp_buf && samples > best_num_samp) ) {
				best_fbc = i;
				best_num_samp = samples;
			}
			if ( worst_fbc < 0 || !samp_buf || samples < worst_num_samp )
				worst_fbc = i;
			worst_num_samp = samples;
		}
		XFree( vi );
	}
	GLXFBConfig bestFbc = fbc[ best_fbc ];
	XFree( fbc ); // Make sure to free this!

	
	XVisualInfo* visual = glXGetVisualFromFBConfig( display, bestFbc );
	if (visual == 0) {
		std::cout << "Could not create correct visual window.\n";
		XCloseDisplay(display);
		return 1;
	}
	
	if (screenId != visual->screen) {
		std::cout << "screenId(" << screenId << ") does not match visual->screen(" << visual->screen << ").\n";
		XCloseDisplay(display);
		return 1;

	}

	// Open the window
	XSetWindowAttributes windowAttribs;
	windowAttribs.border_pixel = BlackPixel(display, screenId);
	windowAttribs.background_pixel = WhitePixel(display, screenId);
	windowAttribs.override_redirect = True;
	windowAttribs.colormap = XCreateColormap(display, RootWindow(display, screenId), visual->visual, AllocNone);
	windowAttribs.event_mask = ExposureMask;
	window = XCreateWindow(display, RootWindow(display, screenId), 0, 0, width, height, 0, visual->depth, InputOutput, visual->visual, CWBackPixel | CWColormap | CWBorderPixel | CWEventMask, &windowAttribs);

	// Redirect Close
	Atom atomWmDeleteWindow = XInternAtom(display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(display, window, &atomWmDeleteWindow, 1);

	//Set Title
	setTitle(title);

	// Create GLX OpenGL context
	glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
	glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );
	
	int context_attribs[] = {
		GLX_CONTEXT_MAJOR_VERSION_ARB, JGL_MAJOR,
		GLX_CONTEXT_MINOR_VERSION_ARB, JGL_MINOR,
		GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		None
	};

	GLXContext context = 0;
	const char *glxExts = glXQueryExtensionsString( display,  screenId );
	if (!isExtensionSupported( glxExts, "GLX_ARB_create_context")) {
		std::cout << "GLX_ARB_create_context not supported\n";
		context = glXCreateNewContext( display, bestFbc, GLX_RGBA_TYPE, 0, True );
	}
	else {
		context = glXCreateContextAttribsARB( display, bestFbc, 0, true, context_attribs );
	}
	XSync( display, False );

	// Verifying that context is a direct context
	if (!glXIsDirect (display, context)) {
		std::cout << "Indirect GLX rendering context obtained\n";
	}
	else {
		std::cout << "Direct GLX rendering context obtained\n";
	}
	glXMakeCurrent(display, window, context);

	//Register error logger
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	std::cout << "GL Renderer: " << glGetString(GL_RENDERER) << "\n";
	std::cout << "GL Version: " << glGetString(GL_VERSION) << "\n";
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

	if (!init()) {
		glXDestroyContext(display, context);
		XFree(visual);
		XFreeColormap(display, windowAttribs.colormap);
		XDestroyWindow(display, window);
		XCloseDisplay(display);
		return 1;
	}

	// Show the window
	XClearWindow(display, window);
	XMapRaised(display, window);

	double prevTime = getMilliseconds();
	double currentTime = getMilliseconds();
	double deltaTime = 0.0;

	timeval time;
	long sleepTime = 0;
	gettimeofday(&time, NULL);
	long nextGameTick = (time.tv_sec * 1000) + (time.tv_usec / 1000);

	// select kind of events we are interested in
	XSelectInput(display, window, KeyPressMask | KeyReleaseMask | ExposureMask);

	//REMVOE FOR KEYS ONLY
	unsigned int keyPos = 0;

	// Enter message loop
	bool running = true;
	while (running) {
		if (XPending(display) > 0) {
			XNextEvent(display, &ev);
			switch (ev.type)
			{
				case Expose:
					XWindowAttributes attribs;
					XGetWindowAttributes(display, window, &attribs);
					resize(attribs.width, attribs.height);
					break;

				case ClientMessage:
					if (ev.xclient.data.l[0] == atomWmDeleteWindow)
						running = false;
					break;
				
				case DestroyNotify:
					running = false;
					break;

				case KeyPress:
					if(keyPos < JKEY_NUM-1)
					{
						setKeymap(ev.xkey.keycode, keyPos++);
						printf("Please press %10s\n", keyNames[keyPos]);
					} else
					{
						printKeymap();
					}
					
					break;

				case KeyRelease:
					//printf("Key released: %x\n", ev.xkey.keycode);
					break;

				default:
					break;
			}
		}

		currentTime = getMilliseconds();
		deltaTime = double(currentTime - prevTime) * 0.001;
		prevTime = currentTime;

		if (!update((float)deltaTime)) {
			break;
		}

		// Present frame
		glXSwapBuffers(display, window);

		gettimeofday(&time, NULL);
		nextGameTick += SKIP_TICKS;
		sleepTime = nextGameTick - ((time.tv_sec * 1000) + (time.tv_usec / 1000));
		usleep((unsigned int)(sleepTime / 1000));
	}

	std::cout << "Shutting Down\n";
	quit();

	// Cleanup GLX
	glXDestroyContext(display, context);

	// Cleanup X11
	XFree(visual);
	XFreeColormap(display, windowAttribs.colormap);
	XDestroyWindow(display, window);
	XCloseDisplay(display);
	return 0;
}

Point GLWindow::getSize()
{
	Point p;
	Window rootWindow;
	int x, y;
	unsigned int width, height, borderWidth, depth;
	XGetGeometry(display, window, &rootWindow, &x, &y, &width, &height, &borderWidth, &depth);
	p.x = width;
	p.y = height;
	return p;
}

Point GLWindow::getPosition()
{
	Point p;
	Window rootWindow;
	int x, y;
	unsigned int width, height, borderWidth, depth;
	XGetGeometry(display, window, &rootWindow, &x, &y, &width, &height, &borderWidth, &depth);
	p.x = x;
	p.y = y;
	return p;
}

Point GLWindow::getCursorPos()
{
	Point p;

	Window rootWindow;
	Window childWindow;
	int absouluteCoordX, absoluteCoordY;
	unsigned int mask_return;
	XQueryPointer(display, window, &rootWindow, &childWindow, &absouluteCoordX, &absoluteCoordY, &p.x, &p.y, &mask_return);
	return p;
}

void GLWindow::showCursor(bool visible)
{
	if(visible)
	{
		XUndefineCursor(display, window);
	}
	else
	{
		Cursor invisibleCursor;
		Pixmap bitmapNoData;
		XColor black;
		static char noData[] = { 0,0,0,0,0,0,0,0 };
		black.red = black.green = black.blue = 0;

		bitmapNoData = XCreateBitmapFromData(display, window, noData, 8, 8);
		invisibleCursor = XCreatePixmapCursor(display, bitmapNoData, bitmapNoData, 
											&black, &black, 0, 0);
		XDefineCursor(display,window, invisibleCursor);
		XFreeCursor(display, invisibleCursor);
		XFreePixmap(display, bitmapNoData);
	}
	
}

void GLWindow::setTitle(const char *title)
{
	XStoreName(display, window, title);
}

long GLWindow::getMilliseconds()
{
	static timeval s_tTimeVal;
	gettimeofday(&s_tTimeVal, NULL);
	double time = s_tTimeVal.tv_sec * 1000.0; // sec to ms
	time += s_tTimeVal.tv_usec / 1000.0; // us to ms
	return time;
}

int main(int argc, char** argv)
{
	GLWindow::pre(argc, argv);
}

#endif // OS_Linux