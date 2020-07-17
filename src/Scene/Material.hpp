#ifndef J3_MATERIAL_H
#define J3_MATERIAL_H

#include "Shader/ShaderProgram.hpp"
#include "CubeMap.hpp"

namespace J3
{
	typedef struct
	{
		
	} Material;
	

	typedef struct
	{
		Material material;
		
		GLuint DIFFUSE;
		GLuint NORMAL;
		GLuint METALLIC;
		GLuint ROUGHNESS;

		CubeMap* cubeMap;
	} PBRMaterial;
}


#endif // J3_MATERIAL_H