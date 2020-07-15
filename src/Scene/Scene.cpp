#include "Scene.h"

using namespace J3;

Scene::Scene()
{

}

void Scene::update()
{
	for(Node& n : nodes)
	{
		// TODO Update Nodes
	}
}

void Scene::render()
{
	for(Node& n : nodes)
	{
		// TODO Render Nodes
	}
}

Scene::~Scene()
{

}