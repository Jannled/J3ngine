#include "Scene.h"

#include "lib/JUtils.h"

#include <iostream>

#include "lib/Galogen46.h"
#include "lib/tiny_obj_loader.h"

Scene::Scene(Camera& camera)
{
	this->camera = &camera;
}

Scene::~Scene()
{

}

Camera* Scene::getCamera()
{
	return this->camera;
}

Scene* Scene::loadScene(const char* path, Camera& camera)
{
	Scene* scene = new Scene(camera);

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	std::string warn;
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path, "models/", true, false);

	if (!warn.empty())
		std::cout << warn << std::endl;

	if (!err.empty())
		std::cerr << err << std::endl;

	if(ret)
	{
		for(const auto& shape : shapes) 
		{
			for(const auto& index : shape.mesh.indices) 
			{
				vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]);
				vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
				vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);
				indices.push_back(indices.size());
			}

			scene->models.push_back(Model(
				&vertices[0], vertices.size(), 
				&indices[0], indices.size()
			));
		}
	}
	else
	{
		std::cerr << "Failed to open " << path << std::endl;
		return NULL;
	}
	
	return scene;
}

void Scene::render(ShaderProgram program)
{
	for(Model m : models)
	{
		m.render(program, *camera);
	}
}