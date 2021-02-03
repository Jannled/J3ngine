#include "StaticMesh.hpp"


using namespace J3;

StaticMesh::StaticMesh(Mesh& mesh) : mesh(mesh)
{

}

StaticMesh::~StaticMesh()
{

}

void StaticMesh::render(glm::mat4 viewProjection)
{
	PBRMaterial& mat = *mesh.materials;
	mat.program->use();

    prepare(mat);

	glBindVertexArray(mesh.VAO);

	glm::mat4 model = glm::translate(position) * glm::toMat4(rotation) * glm::scale(scaling);
	glm::mat4 transform = viewProjection * model;
	glm::mat3 modelNormal = glm::mat3(glm::transpose(glm::inverse(model)));

	//mat.program->setMat4f(UNIFORM_TRANSFORM, transform);
	//mat.program->setMat4f(UNIFORM_MODELSPACE, model);
	mat.program->setMat3f(UNIFORM_MODELNORMAL, modelNormal);

	//printf("Texture: %d\n", material.DIFFUSE);
	glDrawElements(GL_TRIANGLES, mesh.cIndices, GL_UNSIGNED_INT, 0);
}

void StaticMesh::prepare(PBRMaterial& material)
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
}