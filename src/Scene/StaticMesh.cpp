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