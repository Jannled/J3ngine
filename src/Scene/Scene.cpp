#include "Scene.h"

#include <iostream>
#include <stdio.h>
#include <string.h>

#include "lib/Galogen46.h"
#include "lib/tiny_obj_loader.h"
#include "Scene/Loader/ModelLoader.h"

Scene::Scene(Camera& camera, CubeMap& skybox)
{
	this->camera = &camera;
	this->cubemap = &skybox;
}

Scene::~Scene()
{

}

Camera* Scene::getCamera()
{
	return this->camera;
}

bool Scene::loadToScene(File& file)
{
	return Loader::loadOBJ(file, models);
}

void Scene::update()
{
	for(Node& n : models)
		n.update();
}

void Scene::render(ShaderProgram program)
{
	program.use();

	float lightPos[] = {5.0f, 5.0f, 1.0f};
	float lightCol[] = {150.0f, 150.0f, 150.0f};

	program.setVec3f("lightPositions", lightPos);
	program.setVec3f("lightColors", lightCol);

	program.setVec3f("camPos", *camera->getPosition());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->getIrradianceMap());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->getPrefilterMap());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, cubemap->getBRDFLUT());

	for(Model m : models)
	{
		m.render(program, *camera);
	}

	cubemap->renderSkybox(*camera);
}