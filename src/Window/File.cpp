#include "File.hpp"

#include <stdio.h>
#include <string.h>

// TODO Let CMake detect the OS
#ifdef _WIN32	
#define OS_WINDOWS
#include <windows.h> //Wont compile without it when using MSVC, worked fine on MingW
#include <io.h>
#include <direct.h> // _getcwd
#include <conio.h>
#include <stdlib.h>
#include <direct.h>
#include <fileapi.h>
#ifndef PATH_MAX
#define PATH_MAX MAX_PATH
#endif

#elif defined __unix__
#define OS_LINUX
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h>

#else
#error "J3File: Unknown OS!"
#endif

File::File()
{
	init(".");
}

File::File(const char* path)
{
	init(path);
}

void File::init(const char* path)
{
	this->path = path;
	this->canonicalPath = toCanonicalPath(path, NULL);

	char* parentString = new char[PATH_MAX];
	char* nameString = new char[PATH_MAX];

	#ifdef OS_WINDOWS
	this->name = new char[PATH_MAX];
	char sDrive[_MAX_DRIVE];
	char sDir[_MAX_DIR];
	char sFName[_MAX_FNAME];
	char sExt[_MAX_EXT];

	_splitpath_s(canonicalPath, sDrive, sDir, sFName, sExt);
	snprintf(nameString, 4096, "%s%s", sFName, sExt);
	snprintf(parentString, 4096, "%s%s", sDrive, sDir);

	this->name = nameString;
	this->parent = parentString;

	#elif defined OS_LINUX
	char* fileName = strdup(canonicalPath);
	char* DirName = strdup(canonicalPath);
	this->name = basename(fileName);

	snprintf(parentString, 4096, "%s%c", dirname(DirName), isDirectory() ? FILESEP : '\0');
	this->parent = parentString;
	#endif
}

const char* File::getName()
{
	return name;
}

const char* File::getPath()
{
	return path;
}

const char* File::getCanonicalPath()
{
	return canonicalPath;
}

const char* File::getParent()
{
	if(!canonicalPath)
		return NULL;
		
	return parent;
}

File& File::getParentFile()
{
	return *(new File(getParent()));
}

bool File::exists()
{
	#ifdef OS_WINDOWS
	DWORD dwAttrib = GetFileAttributes(path);
    if (dwAttrib == 0xFFFFFFFF)
        return false;
    return true;

	#elif defined OS_LINUX
	return (access(path, F_OK) != -1);
	#endif
}

bool File::isDirectory()
{
	#ifdef OS_WINDOWS
	DWORD dwAttrib = GetFileAttributes(path);
	return 	(dwAttrib != INVALID_FILE_ATTRIBUTES && 
			(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));

	#elif defined OS_LINUX
	struct stat path_stat;
	if(stat(path, &path_stat))
		return false;
	return S_ISDIR(path_stat.st_mode);
	#endif
}

bool File::isFile()
{
	#ifdef OS_WINDOWS
	DWORD dwAttrib = GetFileAttributes(path);
	return 	(dwAttrib != INVALID_FILE_ATTRIBUTES && 
			(dwAttrib & FILE_ATTRIBUTE_NORMAL));
	#elif defined OS_LINUX
	struct stat path_stat;
	if(!stat(path, &path_stat))
		return false;
	return S_ISREG(path_stat.st_mode);
	#endif
}

const char* File::toCanonicalPath(const char* path, char* buff)
{
	if(!buff)
		buff = new char[PATH_MAX];

	#ifdef OS_WINDOWS
	_fullpath(buff, path, PATH_MAX); //Maybe GetFullPathName() come in handy sometime
	return buff;

	#elif defined OS_LINUX
	return realpath(path, buff);
	#endif
}

const char* File::getWorkingDirectory(char *buf, unsigned int size)
{
	#ifdef OS_WINDOWS
	return _getcwd(buf, size);
	#elif defined OS_LINUX
	return getcwd(buf, size);
	#endif
}

File::~File()
{
	//delete[] path;
	//delete[] canonicalPath;
}
