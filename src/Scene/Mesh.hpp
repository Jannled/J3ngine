#ifndef J3_MESH_H
#define J3_MESH_H

#include "VertexBuffer.hpp"
#include "Material.hpp"

namespace J3
{
	typedef struct
	{
		GLuint VAO;

		VertexBuffer vertices;
		VertexBuffer normals;
		VertexBuffer texCoords;

		GLvoid* indices;
		GLuint INDICES;
		GLsizei cIndices;
		
		PBRMaterial* materials;
		size_t cMaterials;
	} Mesh;
}


#endif // J3_MESH_H