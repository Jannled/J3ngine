#include "lib/Galogen46.h"

#include "Scene/Camera/Camera.h"
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

typedef struct {
	GLvoid* data; /**< Pointer to an element array */
	size_t dataLength; /**< Number of elements in the array */
	GLenum type; /**< Type of elements in the array, see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml */
	GLuint attribIndex; /**< Index of the vertex attribute in the ShaderProgram */
	GLint vecDim = 3; /**< Amount of elements per vector */
	GLsizei stride = 0; /**< Space between vectors */
	GLvoid* offset = (void*) 0; /**< Offset in the vertex buffer */
	GLuint ID = 0; /**< OpenGL buffer handle */
} VertexBuffer;

typedef struct
{
	GLuint DIFFUSE;
	GLuint NORMAL;
	GLuint METALLIC;
	GLuint ROUGHNESS;
} PBRMaterial;

typedef struct
{
	GLuint VAO;

	VertexBuffer vertices;
	VertexBuffer normals;
	VertexBuffer texCoords;

	GLuint INDICES;
	GLuint cIndices;
} Mesh;

class Model : public Node
{
	public:
		Model(Mesh mesh, PBRMaterial textures);
		virtual ~Model();

		void render(ShaderProgram &shaderProgram, Camera &cam);

		static GLuint loadTexture(char const * path);
		static GLuint loadTexture(char const * path, GLint wrapS, GLint wrapT, GLint minFilter, GLint magFilter, bool generateMipMaps);
		static GLint loadArrayBuffer(VertexBuffer &buffer);
		static GLuint loadArrayBuffer(float* data, unsigned int count, GLenum usage, GLuint attribIndex, GLuint componentCount);
		static GLuint loadArrayBuffer(float* data, unsigned int count, GLenum usage, GLuint attribIndex, GLuint componentCount, GLsizei stride, const void* offset);
		static GLuint loadElementBuffer(unsigned int* data, unsigned int count, GLenum usage);

	private:
		Mesh mesh;
		PBRMaterial material;
};

#endif // MODEL_H