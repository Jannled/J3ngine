#include "Model.h"

#include "lib/stb/stb_image.h"

#include "lib/glm/gtc/matrix_transform.hpp"
#include "lib/glm/gtx/transform.hpp"

#include <iostream>

Model::Model(Mesh data, PBRMaterial textures)
	: Node(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f))
{
	this->mesh = data;
	this->material = textures;
}

void Model::render(ShaderProgram &shaderProgram, Camera &cam)
{
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, material.DIFFUSE);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, material.NORMAL);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, material.METALLIC);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, material.ROUGHNESS);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(mesh.VAO);

	glm::mat4 model = glm::translate(position) * glm::toMat4(rotation) * glm::scale(scale);
	glm::mat4 transform = cam.viewProjection() * model;
	glm::mat3 modelNormal = glm::mat3(glm::transpose(glm::inverse(model)));

	shaderProgram.setMat4f(UNIFORM_TRANSFORM, transform);
	shaderProgram.setMat4f(UNIFORM_MODELSPACE, model);
	shaderProgram.setMat3f(UNIFORM_MODELNORMAL, modelNormal);

	//printf("Texture: %d\n", material.DIFFUSE);
	glDrawElements(GL_TRIANGLES, mesh.cIndices, GL_UNSIGNED_INT, 0);
}

GLuint Model::loadArrayBuffer(float* data, unsigned int count, GLenum usage, GLuint attribIndex, GLuint componentCount)
{
	return loadArrayBuffer(data, count, usage, attribIndex, componentCount, 0, (void*) 0);
}

GLint Model::loadArrayBuffer(VertexBuffer &buffer)
{
	size_t elementSize = 
		(buffer.type==GL_UNSIGNED_SHORT) ? sizeof(GLushort) : 
		(buffer.type==GL_INT) ? sizeof(GLint) : 
		(buffer.type==GL_UNSIGNED_INT) ? sizeof(GLuint) :
		(buffer.type==GL_FLOAT) ? sizeof(GLfloat) : 
		0;

	glGenBuffers(1, &buffer.ID);
	glBindBuffer(GL_ARRAY_BUFFER, buffer.ID);
	glBufferData(GL_ARRAY_BUFFER, elementSize*buffer.dataLength, buffer.data, GL_STATIC_DRAW);
	glVertexAttribPointer(buffer.attribIndex, buffer.vecDim, buffer.type, GL_FALSE, buffer.stride, buffer.offset);
	glEnableVertexAttribArray(buffer.attribIndex);

	return buffer.ID;
}

GLuint Model::loadArrayBuffer(float* data, unsigned int count, GLenum usage, GLuint attribIndex, GLuint componentCount, GLsizei stride, const void* offset)
{
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data[0])*count, &data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(attribIndex, componentCount, GL_FLOAT, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(attribIndex);

	return bufferID;
}

GLuint Model::loadElementBuffer(unsigned int* data, unsigned int count, GLenum usage)
{
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data[0])*count, &data[0], GL_STATIC_DRAW);

	return bufferID;
}

GLuint Model::loadTexture(char const * path)
{
	return loadTexture(path, GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, true);
}

GLuint Model::loadTexture(char const * path, GLint wrapS, GLint wrapT, GLint minFilter, GLint magFilter, bool generateMipMaps)
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

Model::~Model()
{
	//glDeleteBuffers()
}