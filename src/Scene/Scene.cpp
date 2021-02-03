#include "Scene.hpp"

#include "Galogen46.h"

#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include <stack>

using namespace J3;

Scene::Scene(Camera& camera) : camera(camera)
{
	glClearColor(1.0, 1.0, 1.0, 0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	rootNode = new Node("<root>");
}

void Scene::update()
{
	// TODO implement recursion / use renderTargets

	for(Node& node : rootNode->children)
	{
		node.update();
	}
}

void Scene::render()
{
	if(cubeMap)
		cubeMap->renderSkybox(camera);

	glm::mat4 viewProj = camera.viewProjection();

	//std::cout << glm::to_string(viewProj) << std::endl;

	for(StaticMesh& n : renderTargets)
	{
		n.render(viewProj);
	}
}

void Scene::setResolution(GLuint width, GLuint height)
{
	camera.setResolution(width, height);
}

void Scene::appendChild(StaticMesh& node)
{
	appendChild(node, *rootNode);
}

void Scene::appendChild(StaticMesh& node, Node& appendTo)
{
	renderTargets.push_back(node);
	appendTo.children.push_back(node);
}

void Scene::appendChild(Node& node) 
{
	appendChild(node, *rootNode);
}

void Scene::appendChild(Node& node, Node& appendTo) 
{
	appendTo.children.push_back(node);
}

Scene::~Scene()
{

}