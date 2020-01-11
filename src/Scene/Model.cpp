#include "Model.h"

#include <glm/gtc/matrix_transform.hpp>
#include <lib/glm/gtx/transform.hpp>

Model::Model(float vertices[], size_t cVertices, unsigned int indices[], size_t cIndices)
{
	this->cVertices = cVertices;
	this->cIndices = cIndices;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*vertices)*cVertices, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*indices)*cIndices, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0); 
}

Model::Model(GLuint VAO, GLuint VBO, GLuint cVertices, GLuint EBO, GLuint cIndices)
{
	this->VAO = VAO;
	this->VBO = VBO;
	this->EBO = EBO;

	this->cVertices = cVertices;
	this->cIndices = cIndices;
}

void Model::render(ShaderProgram &shaderProgram, Camera &cam)
{
	glBindVertexArray(VAO);

	glm::mat4 transform = cam.viewProjection() * glm::translate(position) * glm::toMat4(rotation) * glm::scale(scale);

	shaderProgram.setMat4f(UNIFORM_TRANSFORM, transform);

	glDrawElements(GL_TRIANGLES, cIndices, GL_UNSIGNED_INT, 0);
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

Model::~Model()
{
	//glDeleteBuffers()
}