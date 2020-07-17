#include "ShaderProgram.hpp"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>

using namespace J3;

ShaderProgram::ShaderProgram(Shader &vertexShader, Shader &fragmentShader) : programID(glCreateProgram())
{
	init(vertexShader, fragmentShader);
}

ShaderProgram::ShaderProgram(const char* vertexShader, const char* fragmentShader) : programID(glCreateProgram())
{
	Shader *svert = new Shader(vertexShader, GL_VERTEX_SHADER);
	svert->compile();
	Shader *sfrag = new Shader(fragmentShader, GL_FRAGMENT_SHADER);
	sfrag->compile();
	init(*svert, *sfrag);
}

void ShaderProgram::init(Shader &vertexShader, Shader &fragmentShader)
{
	shaders = new Shader[2]{vertexShader, fragmentShader};
	glAttachShader(programID, vertexShader.handle);
	glAttachShader(programID, fragmentShader.handle);
}

void ShaderProgram::link()
{
	// TODO Print out error log when Linking failed!
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
	glUseProgram(programID);
}

GLint ShaderProgram::getUniformLocation(const char* name)
{
	return glGetUniformLocation(programID, name);
}

void ShaderProgram::setBool(const char* name, bool value)
{
	// TODO Implement setBool
}

void ShaderProgram::setInt(const char* name, int value)
{
	glUniform1i(glGetUniformLocation(programID, name), value); 
}

void ShaderProgram::setFloat(const char* name, float value)
{
	glUniform1f(glGetUniformLocation(programID, name), value); 
}

void ShaderProgram::setVec3f(const char* name, float* value)
{
	glUniform3fv(glGetUniformLocation(programID, name), 1, value);
}

void ShaderProgram::setVec3f(const char* name, glm::vec3 value)
{
	glUniform3fv(glGetUniformLocation(programID, name), 1, glm::value_ptr(value));
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
	// TODO Free up ShaderProgram
}