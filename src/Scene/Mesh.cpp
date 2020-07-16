#include "Mesh.h"

using namespace J3;

Mesh::Mesh()
{

}

Mesh::Mesh(Material* material)
{
	this->material = material;
}
	
Mesh::~Mesh()
{
	// TODO Free up ShaderProgram
}