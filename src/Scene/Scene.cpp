#include "Scene.h"

#include "lib/JUtils.h"

#include <iostream>
#include <stdio.h>
#include <string.h>

#include "lib/Galogen46.h"
#include "lib/tiny_obj_loader.h"

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

bool Scene::loadToScene(const char* path)
{
	loadToScene(path, "models/");
}

bool Scene::loadToScene(const char* path, const char* baseDir)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> texCoords;
	std::vector<GLuint> indices;

	std::string warn;
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path, baseDir, true, false);

	if (!warn.empty())
		std::cout << warn << std::endl;

	if (!err.empty())
		std::cerr << err << std::endl;

	if(ret)
	{
		pbrTextures textures[materials.size()] = {0};

		for(int i=0; i<materials.size(); i++)
		{
			if(materials[i].diffuse_texname.size() > 0)
			{
				char dpath[1024] = {0};
				strncat(dpath, baseDir, 1024);
				strncat(dpath, materials[i].diffuse_texname.c_str(), 1024);
				textures[i].DIFFUSE = Model::loadTexture(dpath);
			}
			
			if(materials[i].normal_texname.size() > 0)
			{
				char npath[1024] = {0};
				strncat(npath, baseDir, 1024);
				strncat(npath, materials[i].normal_texname.c_str(), 1024);
				textures[i].NORMAL = Model::loadTexture(npath);
			}

			if(materials[i].metallic_texname.size() > 0)
			{
				char mpath[1024] = {0};
				strncat(mpath, baseDir, 1024);
				strncat(mpath, materials[i].metallic_texname.c_str(), 1024);
				textures[i].METALLIC = Model::loadTexture(mpath);
			}

			if(materials[i].roughness_texname.size() > 0)
			{
				char rpath[1024] = {0};
				strncat(rpath, baseDir, 1024);
				strncat(rpath, materials[i].roughness_texname.c_str(), 1024);
				textures[i].ROUGHNESS = Model::loadTexture(rpath);
			}
		}
		
		int i=0;
		for(const auto& shape : shapes) 
		{
			unsigned int materialID = (shape.mesh.material_ids.size() > 0) ? shape.mesh.material_ids[0] : 0;

			int j=0;
			for(const auto& index : shape.mesh.indices) 
			{
				if(j < shape.mesh.material_ids.size())
					if(shape.mesh.material_ids[j++] != materialID)
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

			glGenVertexArrays(1, &glData.VAO);
			glBindVertexArray(glData.VAO);

			glData.VERTICES = Model::loadArrayBuffer(&vertices[0], vertices.size(), GL_STATIC_DRAW, 0, 3);
			glData.cVertices = vertices.size();

			glData.NORMALS  = Model::loadArrayBuffer(&normals[0], normals.size(), GL_STATIC_DRAW, 1, 3);
			glData.cNormals = normals.size();

			glData.TEXCOORDS = Model::loadArrayBuffer(&texCoords[0], texCoords.size(), GL_STATIC_DRAW, 2, 2);
			glData.cTexcoords = texCoords.size();

			glData.INDICES = Model::loadElementBuffer(&indices[0], indices.size(), GL_STATIC_DRAW);
			glData.cIndices = indices.size();

			glBindBuffer(GL_ARRAY_BUFFER, 0); 
			glBindVertexArray(0); 

			models.push_back(Model(glData, textures[materialID]));
		}
	}
	else
	{
		std::cerr << "Failed to open " << path << std::endl;
		return false;
	}
	
	return true;
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

	for(Model m : models)
	{
		m.render(program, *camera);
	}

	cubemap->renderSkybox(*camera);
}