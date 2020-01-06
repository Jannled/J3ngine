#include "Utils.h"

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#ifdef _WIN32
#include <stdlib.h>

char *absolutePath(const char *relativePath, char *absolutePath)
{
	return _fullpath(absolutePath, relativePath, 1024);
}

#elif __linux__
#include <limits.h>
#include <stdlib.h>

char *absolutePath(const char *relativePath, char *absolutePath)
{
	if(absolutePath == NULL)
		absolutePath = malloc(PATH_MAX);

	realpath(relativePath, absolutePath);
}

#endif
