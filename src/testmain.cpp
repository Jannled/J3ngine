#include "AWindow/AWindow.h"

#include <stdio.h>
#include <iostream>
#include "lib/Galogen46.h"

#include "Model/Model.h"
#include "Shader/Shader.h"
#include "Shader/ShaderProgram.h"

Shader *vshader;
Shader *fshader;
ShaderProgram *program;

Model *model;

//Geometry stuff
unsigned int VAO;

void GLWindow::pre(int argc, char** argv)
{
	std::cout << "Starting program with args: [";
	for(int i=0; i<argc; i++)
		std::cout << "\"" << argv[i] << "\"" << ((i<argc-1) ? ", " : "");
	std::cout << "]" << std::endl;

	GLWindow::show("J3ngine", 1280, 720);
}

bool GLWindow::init()
{
	glClearColor(1.0, 1.0, 1.0, 0);

	vshader = new Shader("./src/Shader/simple_vertex.glsl", GL_VERTEX_SHADER);
	fshader = new Shader("./src/Shader/simple_fragment.glsl", GL_FRAGMENT_SHADER);

	vshader->compile();
	fshader->compile();

	program = new ShaderProgram(*vshader, *fshader);
	program->link();

	//Test Geometry
	float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    
    model = new Model(vertices, 12, indices, 6);

	return true;
}

bool GLWindow::update(float delta)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program->use();
	model->render(*program);

	return true;
}

void GLWindow::quit()
{
	
}

void GLWindow::resize(int width, int height)
{
	printf("Resize to %dx%d\n", width, height);
}