#include "AWindow/AWindow.h"

#include <stdio.h>
#include <iostream>
#include "lib/Galogen46.h"
#include "Shader/Shader.h"
#include "Shader/ShaderProgram.h"

Shader *vshader;
Shader *fshader;
ShaderProgram *program;

//Geometry stuff
unsigned int VAO;

int main(int argc, char** argv)
{
	std::cout << "Starting program with args: [";
	for(int i=0; i<argc; i++)
		std::cout << "\"" << argv[i] << "\"" << ((i<argc-1) ? ", " : "");
	std::cout << "]" << std::endl;

	GLWindow::show("Hallo Welt", 1280, 720);
}

void GLWindow::pre()
{

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
    unsigned int VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

	return true;
}

bool GLWindow::update(float delta)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program->use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	return true;
}

void GLWindow::quit()
{
	
}

void GLWindow::resize(int width, int height)
{
	printf("Resize to %dx%d\n", width, height);
}