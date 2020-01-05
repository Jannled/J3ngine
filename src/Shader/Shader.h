#ifndef SHADER_H
#define SHADER_H

#include "lib/Galogen46.h"

class Shader
{
public:
	Shader(const char *filepath, GLenum type);
	virtual ~Shader();
	int compile();

	GLenum type;
	int shaderID = -1;
};

#endif //SHADER_H
