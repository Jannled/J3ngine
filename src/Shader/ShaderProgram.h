#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "lib/Galogen46.h"
#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(Shader &vertexShader, Shader &fragmentShader);
	virtual ~ShaderProgram();
	void link();
	void use();

	int programID;
};

#endif //SHADERPROGRAM_H
