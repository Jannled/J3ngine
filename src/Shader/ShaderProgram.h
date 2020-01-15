#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "lib/Galogen46.h"
#include "lib/glm/glm.hpp"
#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(Shader &vertexShader, Shader &fragmentShader);
	virtual ~ShaderProgram();

	void link();
	void use();

	GLint getUniformLocation(const char* name);

	void setBool(const char* name, bool value);
	void setInt(const char* name, int value);
	void setFloat(const char* name, float value);
	void setMat3f(const char* name, glm::mat3 value);
	void setMat4f(const char* name, float *value, GLboolean transpose);
	void setMat4f(const char* name, glm::mat4 value);

	private:
		int programID;
};

#endif //SHADERPROGRAM_H
