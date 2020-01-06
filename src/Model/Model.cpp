#include "Model.h"

#include <glm/gtc/matrix_transform.hpp>

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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0); 
}

void Model::render(ShaderProgram &shaderProgram)
{
	glBindVertexArray(VAO);

	glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::translate(trans, position);
	//trans = glm::scale(trans, scale);

	shaderProgram.setMat4f("translate", trans);

	glDrawElements(GL_TRIANGLES, cIndices, GL_UNSIGNED_INT, 0);
}

Model::~Model()
{

}