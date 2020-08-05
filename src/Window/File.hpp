#ifndef FILE_H
#define FILE_H

#ifdef _WIN32
#define OS_WINDOWS
#define FILESEP '\\'
#elif __linux__
#define OS_LINUX
#define FILESEP '/'
#endif

class File
{
	public:
		File();
		File(const char* path);
		~File();

		const char* getName();
		const char* getPath();
		const char* getCanonicalPath();
		const char* getParent();
		File& getParentFile();
		bool exists();
		bool isDirectory();
		bool isFile();

		static const char *getWorkingDirectory(char *buf, unsigned int size);
		static const char* toCanonicalPath(const char* path, char* buff);

		private:
			void init(const char* path);
			const char* path;
			const char* parent;
			const char* name;
			const char* canonicalPath;
};

#endif // FILE_H