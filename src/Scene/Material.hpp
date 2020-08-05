#ifndef J3_MATERIAL_H
#define J3_MATERIAL_H

#include "Shader/ShaderProgram.hpp"
#include "CubeMap.hpp"

namespace J3
{
	typedef struct
	{
		ShaderProgram& program;

		GLuint DIFFUSE;
	} Material;
	

	typedef struct PBRMaterial : Material
	{
		GLuint NORMAL;
		GLuint METALLIC;
		GLuint ROUGHNESS;

		CubeMap* cubeMap;
	} PBRMaterial;
}


#endif // J3_MATERIAL_H