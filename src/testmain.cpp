#include "AWindow/AWindow.h"

#include <stdio.h>
#include "lib/Galogen46.h"
#include "Shader/Shader.h"

int main(int argc, char** argv)
{
	printf("Starting program with %d arguments\n", argc);
	GLWindow::show("Hallo Welt", 1280, 720);
}

void GLWindow::pre()
{

}

bool GLWindow::init()
{
	glClearColor(1.0, 1.0, 1.0, 0);

	Shader *vshader = new Shader("Shader/simple_vertex.glsl", GL_VERTEX_SHADER);
	Shader *fshader = new Shader("Shader/simple_fragment.glsl", GL_FRAGMENT_SHADER);

	vshader->compile();
	fshader->compile();

	return true;
}

bool GLWindow::update(float delta)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return true;
}

void GLWindow::quit()
{
	
}

void GLWindow::resize(int width, int height)
{
	printf("Resize to %dx%d\n", width, height);
}