#include "AWindow/AWindow.h"

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "lib/Galogen46.h"

#include "Scene/Model.h"
#include "Scene/Scene.h"
#include "Scene/CubeMap.h"
#include "Shader/Shader.h"
#include "Shader/ShaderProgram.h"

Shader* vshader;
Shader* fshader;
ShaderProgram* program;

Scene* scene;

//Geometry stuff
unsigned int VAO;

int _argc;
char** _argv;

void GLWindow::pre(int argc, char** argv)
{
	std::cout << "Starting program with args: [";
	for(int i=0; i<argc; i++)
		std::cout << "\"" << argv[i] << "\"" << ((i<argc-1) ? ", " : "");
	std::cout << "]" << std::endl;

	_argc = argc;
	_argv = argv;

	GLWindow::show("J3ngine", 1280, 720);
}

bool GLWindow::init()
{
	glClearColor(1.0, 1.0, 1.0, 0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	vshader = new Shader("./src/Shader/pbr_vertex.glsl", GL_VERTEX_SHADER);
	fshader = new Shader("./src/Shader/pbr_fragment.glsl", GL_FRAGMENT_SHADER);

	vshader->compile();
	fshader->compile();

	GLWindow::showCursor(true);

	program = new ShaderProgram(*vshader, *fshader);
	program->link();
	program->use();
	program->setInt("irradianceMap", 0);
	program->setInt("prefilterMap", 1);
	program->setInt("brdfLUT", 2);
	program->setInt(TEX_ALBEDO, 3);
	program->setInt(TEX_NORMAL, 4);
	program->setInt(TEX_METALLIC, 5);
	program->setInt(TEX_ROUGNESS, 6);
	program->setInt(TEX_AO, 7);
    
	GLWindow::Point windowSize = GLWindow::getSize();
	printf("Window size: %dx%d\n", windowSize.x, windowSize.y);

	Camera* camera = new Camera(windowSize);
	CubeMap* skybox = new CubeMap("models/Newport_Loft_Ref.hdr");
	scene = new Scene(*camera, *skybox);

	if(_argc > 1)
		scene->loadToScene(_argv[1]);
	else
		scene->loadToScene("models/RustedSphere.obj");

	return true;
}

bool GLWindow::update(float delta)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static float time;
	time += delta;
	float radius = 5;

	program->use();

	if(scene)
	{
		scene->render(*program);
		scene->getCamera()->setPosition(glm::sin(time) * radius, 1.5, glm::cos(time) * radius);
	}

	glFlush();

	return true;
}

void GLWindow::quit()
{
	printf("Window requested to close\n");
}

void GLWindow::resize(int width, int height)
{
	printf("Changed resolution to %dx%d\n", width, height);
	glViewport(0, 0, width, height);
	if(scene)
		scene->getCamera()->setResolution(width, height);
}

void GLWindow::cursorListener(int movex, int movey)
{
	//printf("Cursor movement: %dx%d\n", movex, movey);
}

bool GLWindow::keyboardListener(KCode_t key)
{	
	switch (key)
	{
	case K_ESC:
		return false;
	
	default:
		printf("Key pressed: 0x%04X\n", key);
		break;
	}
	return true;
}