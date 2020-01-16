#include "ShaderProgram.h"

#include <iostream>

#include "glm/gtc/type_ptr.hpp"

ShaderProgram::ShaderProgram()
{

}

ShaderProgram::ShaderProgram(Shader &vertexShader, Shader &fragmentShader)
{
	programID = glCreateProgram();
	glAttachShader(programID, vertexShader.shaderID);
	glAttachShader(programID, fragmentShader.shaderID);
}

void ShaderProgram::link()
{
	glLinkProgram(programID);
	GLint reval;
	glGetProgramiv(programID, GL_LINK_STATUS, &reval);
	if(!reval)
	{
		std::cout << "ShaderProgram(" << programID <<") Linking failed" << std::endl;
	}
	else
		std::cout << "ShaderProgram(" << programID <<") Linked sucessfully" << std::endl;
}

void ShaderProgram::use()
{
	//std::cout << "Using shaderprogram with id: " << programID << std::endl;
	glUseProgram(programID);
}

GLint ShaderProgram::getUniformLocation(const char* name)
{
	return glGetUniformLocation(programID, name);
}

void ShaderProgram::setBool(const char* name, bool value)
{

}

void ShaderProgram::setInt(const char* name, int value)
{
	
}

void ShaderProgram::setFloat(const char* name, float value)
{

}

void ShaderProgram::setVec3f(const char* name, float* value)
{
	glUniform3fv(glGetUniformLocation(programID, name), 1, value);
}

void ShaderProgram::setMat4f(const char* name, float *value, GLboolean transpose)
{
	glUniformMatrix4fv(glGetUniformLocation(programID, name), 1, transpose, value);
}

void ShaderProgram::setMat3f(const char* name, glm::mat3 value)
{
	glUniformMatrix3fv(glGetUniformLocation(programID, name), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setMat4f(const char* name, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(programID, name), 1, GL_FALSE, glm::value_ptr(value));
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(programID);
}
