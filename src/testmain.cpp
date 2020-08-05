#include <stdio.h>

#include "Window/Platform.h"
#include "Window/Window.hpp"
#include "Window/WindowManager.hpp"

#include "Window/Window.hpp"

#include "Scene/Camera.hpp"
#include "Scene/Scene.hpp"

J3::Camera* camera;
J3::Scene* scene;

void J3Window::pre(int argc, char** argv)
{
	printf("J3Engine Version %d.%d.%d #%s compiled on %s launched with %d params!\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, GIT_SHORT_HASH, OS_FULLNAME, argc);

	printf("Fenster: %zd\n", J3::WindowManager::getWindowCount());

	J3Window::show("J3ngine", 1280, 720);

	printf("Closing application!");

	//return 0;
}

bool J3Window::init()
{
	Point p = J3Window::getSize();
	camera = new J3::Camera(p.x, p.y);
	scene = new J3::Scene(*camera);
	
	//J3::StaticMesh mesh = new J3::StaticMesh();

	return true;
}

bool J3Window::update(float delta)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static float time;
	time += delta;

	if(scene)
	{
		scene->render();
		
	}

	glFlush();

	return true;
}

void J3Window::resize(int width, int height)
{
	printf("Changed resolution to %dx%d\n", width, height);
	glViewport(0, 0, width, height);
	if(scene)
		scene->setResolution(width, height);
}

void J3Window::quit()
{
	printf("Window requested to close\n");
}

void J3Window::cursorListener(int movex, int movey)
{
	//printf("Cursor movement: %dx%d\n", movex, movey);
}

bool J3Window::keyboardListener(KCode_t key)
{
	return true;
}