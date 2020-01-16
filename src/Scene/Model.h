#include "lib/Galogen46.h"

#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/quaternion.hpp"
#include "lib/glm/gtx/quaternion.hpp"

#include "Camera.h"
#include "Shader/ShaderProgram.h"

#ifndef MODEL_H
#define MODEL_H

#ifndef UNIFORM_TRANSFORM
#define UNIFORM_TRANSFORM "transform"
#endif

#ifndef UNIFORM_MODELNORMAL
#define UNIFORM_MODELNORMAL "modelNormal"
#endif

#ifndef UNIFORM_MODELSPACE
#define UNIFORM_MODELSPACE "modelSpace"
#endif

#ifndef TEX_ALBEDO
#define TEX_ALBEDO "albedoMap"
#endif

#ifndef TEX_NORMAL
#define TEX_NORMAL "normalMap"
#endif

#ifndef TEX_METALLIC
#define TEX_METALLIC "metallicMap"
#endif

#ifndef TEX_ROUGNESS
#define TEX_ROUGNESS "roughnessMap"
#endif

#ifndef TEX_AO
#define TEX_AO "aoMap"
#endif

typedef struct
{
	GLuint VAO;

	GLuint VERTICES;
	GLuint cVertices;

	GLuint NORMALS;
	GLuint cNormals;

	GLuint TEXCOORDS;
	GLuint cTexcoords;

	GLuint INDICES;
	GLuint cIndices;

} GLData;

typedef struct
{
	GLuint DIFFUSE;
	GLuint NORMAL;
	GLuint METALLIC;
	GLuint ROUGHNESS;
} pbrTextures;

class Model
{
	public:
		Model(float vertices[], size_t cVertices, unsigned int indices[], size_t cIndices);
		Model(GLData data, pbrTextures textures);
		virtual ~Model();

		void setPosition(float x, float y, float z);
		void setPosition(glm::vec3 pos);
		void setEulerRotation(float x, float y, float z);
		void setEulerRotation(glm::vec3 rot);

		void render(ShaderProgram &shaderProgram, Camera &cam);

		static GLuint loadTexture(char const * path);
		static GLuint loadArrayBuffer(float* data, unsigned int count, GLenum usage, GLuint attribIndex, GLuint componentCount);
		static GLuint loadArrayBuffer(float* data, unsigned int count, GLenum usage, GLuint attribIndex, GLuint componentCount, GLsizei stride, const void* offset);
		static GLuint loadElementBuffer(unsigned int* data, unsigned int count, GLenum usage);

	private:
		GLData glData;
		pbrTextures textures;

		glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
		glm::quat rotation = glm::quat(glm::vec3(0.0, 0.0, 0.0));
		glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
};

#endif // MODEL_H