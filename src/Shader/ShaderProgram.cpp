#include "ShaderProgram.h"

#include <iostream>

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

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(programID);
}
