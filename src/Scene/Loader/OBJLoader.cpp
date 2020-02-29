#include "ModelLoader.h"

#include <iostream>

#include "lib/tiny_obj_loader.h"

bool Loader::loadOBJ(const char* file, std::vector<Model> models)
{
	if(!models)
		models = new std::vector<Model>();

    tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> texCoords;
	std::vector<GLuint> indices;

	std::string warn;
	std::string err;

	const char* baseDir = file.getParent();
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, file.getCanonicalPath(), baseDir, true, false);

	if (!warn.empty())
		std::cout << warn << std::endl;

	if (!err.empty())
		std::cerr << err << std::endl;

	if(ret)
	{
		//First load Materials and Textures
		PBRMaterial textures = new PBRMaterial[materials.size()];

		for(int i=0; i<materials.size(); i++)
		{
			if(materials[i].diffuse_texname.size() > 0)
			{
				char dpath[1024] = {0};
				snprintf(dpath, 1024, "%s%s", baseDir, materials[i].diffuse_texname.c_str());
				textures[i].DIFFUSE = Model::loadTexture(dpath);
			}
			
			if(materials[i].normal_texname.size() > 0)
			{
				char npath[1024] = {0};
				snprintf(npath, 1024, "%s%s", baseDir, materials[i].normal_texname.c_str());
				textures[i].NORMAL = Model::loadTexture(npath);
			}

			if(materials[i].metallic_texname.size() > 0)
			{
				char mpath[1024] = {0};
				snprintf(mpath, 1024, "%s%s", baseDir, materials[i].metallic_texname.c_str());
				textures[i].METALLIC = Model::loadTexture(mpath);
			}

			if(materials[i].roughness_texname.size() > 0)
			{
				char rpath[1024] = {0};
				snprintf(rpath, 1024, "%s%s", baseDir, materials[i].roughness_texname.c_str());
				textures[i].ROUGHNESS = Model::loadTexture(rpath);
			}
		}
		
		// Then loop over shapes to load the Models
		for (size_t s = 0; s < shapes.size(); s++) 
		{
			GLint materialID = -1;

			vertices.clear();
			normals.clear();
			indices.clear();
			texCoords.clear();

			// Loop over faces(polygon)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) 
			{
				int fv = shapes[s].mesh.num_face_vertices[f];

				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++) 
				{
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					vertices.push_back(attrib.vertices[3*idx.vertex_index+0]);
					vertices.push_back(attrib.vertices[3*idx.vertex_index+1]);
					vertices.push_back(attrib.vertices[3*idx.vertex_index+2]);
					normals.push_back(attrib.normals[3*idx.normal_index+0]);
					normals.push_back(attrib.normals[3*idx.normal_index+1]);
					normals.push_back(attrib.normals[3*idx.normal_index+2]);
					texCoords.push_back(attrib.texcoords[2*idx.texcoord_index+0]);
					texCoords.push_back(attrib.texcoords[2*idx.texcoord_index+1]);
					// Optional: vertex colors
					// tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
					// tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
					// tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];

					indices.push_back(indices.size());
				}
				index_offset += fv;

				// per-face material
				if(materialID < 0)
					materialID = shapes[s].mesh.material_ids[f];
				else if(shapes[s].mesh.material_ids[f] != materialID)
					std::cerr << "Different materials for a single model is not supported right now." << std::endl;
			}

			Mesh mesh = new Mesh();

			glGenVertexArrays(1, &mesh.VAO);
			glBindVertexArray(mesh.VAO);

			mesh.vertices = new {&vertices[0], vertices.size(), GL_FLOAT, 0, 3};
			if(!Model::loadArrayBuffer(mesh.vertices))
				printf("Error while uploading %d vertex elements to the GPU for file %s!", );
			mesh.normals = new {&vertices[0], vertices.size(), GL_FLOAT, 1, 3};
			mesh.texCoords = new {&vertices[0], vertices.size(), GL_FLOAT, 2, 2};

			mesh.INDICES = Model::loadElementBuffer(&indices[0], indices.size(), GL_STATIC_DRAW);
			mesh.cIndices = indices.size();

			glBindBuffer(GL_ARRAY_BUFFER, 0); 
			glBindVertexArray(0); 
			printf("Loaded Model %s with %d vertices and %d faces.\n", shapes[s].name.c_str(), (int) vertices.size(), (int) indices.size());
			models.push_back(Model(mesh, textures[materialID]));
		}
	}
	else
	{
		std::cerr << "Failed to open " << file.getPath() << std::endl;
		return false;
	}
	
	return true;
}