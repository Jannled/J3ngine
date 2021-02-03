#include "ModelLoader.hpp"

#include "stb/stb_image.h"

#include <iostream>

using namespace J3;

ShaderProgram* ModelLoader::pbrShader;

void ModelLoader::loadModel(File& file, Scene& scene) //TODO Load Cameras, lights etc...
{
	if(!pbrShader)
		pbrShader = new J3::ShaderProgram("./Shader/pbr_vertex.glsl", "./Shader/pbr_fragment.glsl");

	Loader::loadOBJ(file, scene);
}

VertexBuffer& ModelLoader::loadArrayBuffer(GLvoid* data, GLenum type, size_t count, GLenum usage, GLuint attribIndex, GLuint componentCount, GLsizei stride, GLvoid* offset)
{
	size_t elementSize = 
		(type==GL_UNSIGNED_SHORT) ? sizeof(GLushort) : 
		(type==GL_INT) ? sizeof(GLint) : 
		(type==GL_UNSIGNED_INT) ? sizeof(GLuint) :
		(type==GL_FLOAT) ? sizeof(GLfloat) : 
		0;

	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, elementSize*count, data, GL_STATIC_DRAW);
	glVertexAttribPointer(attribIndex, componentCount, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(attribIndex);

	VertexBuffer& buff = *(new VertexBuffer);
	buff.ID = bufferID;
	buff.data = data;
	buff.dataLength = count;
	buff.type = type;
	buff.attribIndex = attribIndex;
	buff.vecDim = (GLint) 3;
	buff.stride = stride;
	buff.offset = offset;

	return buff;
}

GLuint ModelLoader::loadElementBuffer(unsigned int* data, unsigned int count, GLenum usage)
{
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data[0])*count, &data[0], GL_STATIC_DRAW);

	return bufferID;
}

GLuint ModelLoader::loadTexture(const char* path)
{
	return loadTexture(path, GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, true);
}

GLuint ModelLoader::loadTexture(const char* path, GLint wrapS, GLint wrapT, GLint minFilter, GLint magFilter, bool generateMipMaps)
{
	stbi_set_flip_vertically_on_load(true);

	unsigned int textureID = 0;
	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		glGenTextures(1, &textureID);

		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		if(generateMipMaps) glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

		std::cout << "Texture(" << textureID << ") loaded from path \"" << path << "\"." << std::endl;

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Failed to load texture \"" << path << "\"" << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}