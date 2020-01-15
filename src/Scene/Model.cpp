#include "Model.h"

#include "lib/stb/stb_image.h"

#include "lib/glm/gtc/matrix_transform.hpp"
#include "lib/glm/gtx/transform.hpp"

#include <iostream>

Model::Model(float vertices[], size_t cVertices, unsigned int indices[], size_t cIndices)
{
	glData.cVertices = cVertices;
	glData.cIndices = cIndices;

	glGenVertexArrays(1, &glData.VAO);
	glGenBuffers(1, &glData.VERTICES);
	glGenBuffers(1, &glData.TEXCOORDS);
	glGenBuffers(1, &glData.INDICES);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(glData.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, glData.VERTICES);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*vertices)*cVertices, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glData.INDICES);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*indices)*cIndices, indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0); 
}

Model::Model(GLData data)
{
	this->glData = data;
}

void Model::render(ShaderProgram &shaderProgram, Camera &cam)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, glData.TEX0);
	
	glBindVertexArray(glData.VAO);

	glm::mat4 model = glm::translate(position) * glm::toMat4(rotation) * glm::scale(scale);
	glm::mat4 transform = cam.viewProjection() * model;
	glm::mat3 modelNormal = glm::mat3(glm::transpose(glm::inverse(model)));

	shaderProgram.setMat4f(UNIFORM_TRANSFORM, transform);
	shaderProgram.setMat3f(UNIFORM_MODELNORMAL, modelNormal);

	glDrawElements(GL_TRIANGLES, glData.cIndices, GL_UNSIGNED_INT, 0);
}

void Model::setPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Model::setPosition(glm::vec3 pos)
{
	this->position = pos;
}

void Model::setEulerRotation(float x, float y, float z)
{
	rotation = glm::quat(glm::vec3(x, y, z));
}

void Model::setEulerRotation(glm::vec3 rot)
{
	rotation = glm::quat(rot);
}

GLuint Model::loadTexture(char const * path)
{
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
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		std::cout << "Texture(" << textureID << ") loaded from path \"" << path << "\"." << std::endl;

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