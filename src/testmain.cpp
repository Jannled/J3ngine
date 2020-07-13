#include <stdio.h>

#include "Info.h"

#include "Window/WindowManager.h"

#include "Scene/Node.h"

void main(int argc, char** argv)
{
	printf("J3Engine Version %d.%d.%d launched with %d params!\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, argc);

	printf("Fenster: %zd\n", J3::WindowManager::getWindowCount());

	new J3::Node();
}