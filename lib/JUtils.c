#include "JUtils.h"

//Linux
#ifdef __linux__
#include <unistd.h>

char *getWorkingDirectory(char *buf, unsigned int size)
{
    return getcwd(buf, size);
}

//Windows
#elif _WIN32
#include <direct.h> // _getcwd

char *getWorkingDirectory(char *buf, size_t size)
{
    return _getcwd(buf, size);
}
#endif

