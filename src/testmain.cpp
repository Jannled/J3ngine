#include <stdio.h>
#include <iostream>

#include "Window/Platform.h"
#include "Window/Window.hpp"
#include "Window/WindowManager.hpp"

#include "Window/Window.hpp"

#include "Scene/Camera.hpp"
#include "Scene/Scene.hpp"
#include "Scene/CubeMap.hpp"

#include "Scene/Loader/ModelLoader.hpp"

J3::Camera* camera;
J3::Scene* scene;

void J3Window::pre(int argc, char** argv)
{
	printf("J3Engine Version %d.%d.%d #%s compiled on %s launched with %d params!\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, GIT_SHORT_HASH, OS_FULLNAME, argc);

	std::cout << "Starting program with args: [";
	for(int i=0; i<argc; i++)
		std::cout << "\"" << argv[i] << "\"" << ((i<argc-1) ? ", " : "");
	std::cout << "]" << std::endl;

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

	camera->lookAt(glm::vec3(5.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	
	//File* testModel = new File("Models/BoomBox.obj");
	File* testModel = new File("C:\\Users\\jannl\\Downloads\\Dark_Astronaut.obj");

	if(testModel && scene)
	{
		J3::ModelLoader::loadModel(*testModel, *scene);
	}

	scene->cubeMap = new J3::CubeMap("C:\\Users\\jannl\\Downloads\\Newport_Loft_Ref.hdr");

	return true;
}

bool J3Window::update(float delta)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static float time;
	time += delta;

	if(scene)
	{
		scene->camera.lookAt(glm::vec3(glm::sin(time) * 5, 0, glm::cos(time) * 5), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
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
	printf("Key pressed: 0x%04X\n", key);
	return true;
}