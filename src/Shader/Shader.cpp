#include "Shader.hpp"

using namespace J3;

#include <iostream>
#include <fstream>
#include <sstream>

#include <limits.h>
#include <stdlib.h>

#include "Window/File.hpp"

Shader::Shader(const char* filePath, GLenum type) : type(type), handle(glCreateShader(type))
{
	File file(filePath);

	switch (type) 
	{
		case GL_VERTEX_SHADER: break;

		case GL_FRAGMENT_SHADER: break;

		default: std::cerr << "Invalid shadertype enum! " << type << std::endl; break;
	}

	std::ifstream inputStream(file.getCanonicalPath(), std::ios::in);
	if(inputStream.is_open())
	{
		std::stringstream sstr;
		sstr << inputStream.rdbuf();
		std::string scode = sstr.str();
		const char* code = scode.c_str();

		glShaderSource(handle, 1, &code, NULL);
	}
	else
	{
		std::cerr << "Failed to open file \"" << file.getCanonicalPath() << "\"." << std::endl;
	}
}

GLint Shader::compile()
{
	if(handle < 1)
	{
		std::cerr << "Can not compile a shader with negative ID!" << std::endl;
		return handle;
	}

	switch(type)
	{
		case GL_VERTEX_SHADER: std::cout << "Compiling Vertex-Shader (" << handle << "): "; break;
		case GL_FRAGMENT_SHADER: std::cout << "Compiling Fragment-Shader (" << handle << "): "; break;
		default: std::cout << "Compiling ?-Shader (" << handle << "): "; break;
	}

	glCompileShader(handle);
	GLint reval;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &reval);
	if(!reval)
	{
		std::cout << "FAIL" << std::endl;
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &reval);
		GLchar *errorLog = new GLchar[reval];  // Why on earth does this have to be on heap now?? Worked fine before
		glGetShaderInfoLog(handle, reval, &reval, &errorLog[0]);
		std::cerr << errorLog << std::endl;
		delete[] errorLog;
		glDeleteShader(handle);
		return reval;
	}
	else
		std::cout << "SUCCESS" << std::endl;

	return reval;
}

GLint Shader::isCompiled()
{
	GLint reval;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &reval);
	return reval;
}

Shader::~Shader()
{
	// TODO Free up Shader
	glDeleteShader(handle);
}