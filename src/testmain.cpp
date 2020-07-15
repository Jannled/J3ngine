#include <stdio.h>

#include "Info.h"

#include "Window/WindowManager.h"

#include "Scene/Camera.h"

void main(int argc, char** argv)
{
	printf("J3Engine Version %d.%d.%d #%s launched with %d params!\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, GIT_SHORT_HASH, argc);

	printf("Fenster: %zd\n", J3::WindowManager::getWindowCount());

	new J3::Camera(1280, 720);
	printf("Closing application!");
}