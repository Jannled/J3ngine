#ifndef J3_MODELLOADER_H
#define J3_MODELLOADER_H

#include "Galogen46.h"
#include "Scene/VertexBuffer.hpp"
#include "Scene/Mesh.hpp"
#include "Scene/Material.hpp"
#include "Shader/ShaderProgram.hpp"
#include "Scene/StaticMesh.hpp"

#include "Window/File.hpp"

namespace J3
{
	class ModelLoader 
	{
		public:

			static StaticMesh* loadModel(File& file);

			static GLuint loadArrayBuffer(float* data, unsigned int count, GLenum usage, GLuint attribIndex, GLuint componentCount);
			static GLuint loadArrayBuffer(VertexBuffer &buffer);
			static GLuint loadArrayBuffer(float* data, unsigned int count, GLenum usage, GLuint attribIndex, GLuint componentCount, GLsizei stride, const void* offset);
			static GLuint loadElementBuffer(unsigned int* data, unsigned int count, GLenum usage);
			static GLuint loadTexture(char const * path);
			static GLuint loadTexture(char const * path, GLint wrapS, GLint wrapT, GLint minFilter, GLint magFilter, bool generateMipMaps);

			static ShaderProgram* pbrShader;
	};
} // namespace J3

#endif // J3_MODELLOADER_H