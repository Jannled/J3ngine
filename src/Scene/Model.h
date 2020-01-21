#include "lib/Galogen46.h"

#include "Camera.h"
#include "Node.h"
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

class Model : public Node
{
	public:
		Model(float vertices[], size_t cVertices, unsigned int indices[], size_t cIndices);
		Model(GLData data, pbrTextures textures);
		virtual ~Model();

		void render(ShaderProgram &shaderProgram, Camera &cam);

		static GLuint loadTexture(char const * path);
		static GLuint loadTexture(char const * path, GLint wrapS, GLint wrapT, GLint minFilter, GLint magFilter, bool generateMipMaps);
		static GLuint loadArrayBuffer(float* data, unsigned int count, GLenum usage, GLuint attribIndex, GLuint componentCount);
		static GLuint loadArrayBuffer(float* data, unsigned int count, GLenum usage, GLuint attribIndex, GLuint componentCount, GLsizei stride, const void* offset);
		static GLuint loadElementBuffer(unsigned int* data, unsigned int count, GLenum usage);

	private:
		GLData glData;
		pbrTextures textures;

		
};

#endif // MODEL_H