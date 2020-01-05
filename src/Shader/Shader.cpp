#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <limits.h>
#include <stdlib.h>

Shader::Shader(const char *filePath, GLenum type)
{
	this->type = type;

	switch (type) {
		case GL_VERTEX_SHADER: break;

		case GL_FRAGMENT_SHADER: break;

		default: std::cerr << "Invalid shadertype enum! " << type << std::endl; break;
	}

	std::ifstream inputStream(filePath, std::ios::in);
	if(inputStream.is_open())
	{
		std::stringstream sstr;
		sstr << inputStream.rdbuf();
		std::string scode = sstr.str();
		const char* code = scode.c_str();

		shaderID = glCreateShader(type);
		glShaderSource(shaderID, 1, &code, NULL);
	}
	else
	{
		char absolutePath[PATH_MAX];
		realpath(filePath, absolutePath);
		std::cerr << "Failed to open file \"" << absolutePath << "\"." << std::endl;
	}
		
	
}

int Shader::compile()
{
	if(shaderID < 0)
	{
		std::cerr << "Can not compile a shader with negative ID!" << std::endl;
		return shaderID;
	}

	switch(type)
	{
		case GL_VERTEX_SHADER: std::cout << "Compiling Vertex-Shader (" << shaderID << "): "; break;
		case GL_FRAGMENT_SHADER: std::cout << "Compiling Fragment-Shader (" << shaderID << "): "; break;
		default: std::cout << "Compiling ?-Shader (" << shaderID << "): "; break;
	}

	glCompileShader(shaderID);
	GLint reval;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &reval);
	if(!reval)
	{
		std::cout << "FAIL" << std::endl;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &reval);
		GLchar errorLog[reval];
		glGetShaderInfoLog(shaderID, reval, &reval, &errorLog[0]);
		std::cerr << errorLog << std::endl;
		glDeleteShader(shaderID);
		return reval;
	}
	else
		std::cout << "SUCCESS" << std::endl;

	return reval;
}

Shader::~Shader()
{
	glDeleteShader(shaderID);
}
