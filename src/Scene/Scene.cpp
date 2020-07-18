#include "Scene.hpp"

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
	// TODO implement recursion
	for(Node& node : rootNode->children)
	{
		node.update();
	}
}

void Scene::render()
{
	if(cubeMap)
		cubeMap->renderSkybox(camera);

	for(StaticMesh& n : renderTargets)
	{
		n.render();
	}
}

Scene::~Scene()
{

}