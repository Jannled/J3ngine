#include "Scene.hpp"

#include "StaticMesh.hpp"

#include "Galogen46.h"

using namespace J3;

Scene::Scene(Camera& camera) : camera(camera)
{
	glClearColor(1.0, 1.0, 1.0, 0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

void Scene::update()
{
	for(Node& n : nodes)
	{
		n.update();
	}
}

void Scene::render()
{
	if(cubeMap)
		cubeMap->renderSkybox(camera);

	for(Node& n : nodes)
	{
		

		n.render();
	}
}

Scene::~Scene()
{

}