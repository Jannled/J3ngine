#include <stdio.h>

#include "Window/Platform.h"

#include "Window/WindowManager.hpp"

#include "Scene/Camera.hpp"
#include "Scene/Scene.hpp"

void main(int argc, char** argv)
{
	printf("J3Engine Version %d.%d.%d #%s compiled on %s launched with %d params!\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, GIT_SHORT_HASH, OS_FULLNAME, argc);

	printf("Fenster: %zd\n", J3::WindowManager::getWindowCount());

	J3::Camera* camera = new J3::Camera(1280, 720);
	J3::Scene* scene = new J3::Scene(*camera);
	printf("Closing application!");
}