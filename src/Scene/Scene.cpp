#include "Scene.h"

#include "lib/JUtils.h"

#include <iostream>
#include <stdio.h>
#include <string.h>

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
	std::vector<GLfloat> normals;
	std::vector<GLfloat> texCoords;
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
		GLuint textures[materials.size()];

		for(int i=0; i<materials.size(); i++)
		{
			char tpath[1024] = {"models/"};
			strncat(tpath, materials[i].diffuse_texname.c_str(), 1024);
			textures[i] = Model::loadTexture(tpath);
		}
		
		int i=0;
		for(const auto& shape : shapes) 
		{
			unsigned int materialID = (shape.mesh.material_ids.size() > 0) ? shape.mesh.material_ids[0] : 0;

			int j=0;
			for(const auto& index : shape.mesh.indices) 
			{
				if(j < shape.mesh.material_ids.size())
					if(!shape.mesh.material_ids[j++] == materialID)
						std::cerr << "Different materials for a single model is not supported right now." << std::endl;

				vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]);
				vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
				vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);

				normals.push_back(attrib.normals[3 * index.normal_index + 0]);
				normals.push_back(attrib.normals[3 * index.normal_index + 1]);
				normals.push_back(attrib.normals[3 * index.normal_index + 2]);

				texCoords.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
				texCoords.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);

				indices.push_back(indices.size());
			}

			GLData glData;
			glData.cVertices = vertices.size();
			glData.cNormals = normals.size();
			glData.cTexcoords = texCoords.size();
			glData.cIndices = indices.size();
			glData.TEX0 = materialID;

			glGenVertexArrays(1, &glData.VAO);
			glGenBuffers(1, &glData.VERTICES);
			glGenBuffers(1, &glData.NORMALS);
			glGenBuffers(1, &glData.TEXCOORDS);
			glGenBuffers(1, &glData.INDICES);
			
			glBindVertexArray(glData.VAO);

			glBindBuffer(GL_ARRAY_BUFFER, glData.VERTICES);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*glData.cVertices, &vertices[0], GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glBindBuffer(GL_ARRAY_BUFFER, glData.NORMALS);
			glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0])*glData.cNormals, &normals[0], GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glBindBuffer(GL_ARRAY_BUFFER, glData.TEXCOORDS);
			glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords[0])*glData.cTexcoords, &texCoords[0], GL_STATIC_DRAW);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glData.INDICES);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0])*glData.cIndices, &indices[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			glBindBuffer(GL_ARRAY_BUFFER, 0); 
			glBindVertexArray(0); 

			scene->models.push_back(Model(glData));
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