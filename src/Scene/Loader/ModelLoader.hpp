#ifndef J3_MODELLOADER_H
#define J3_MODELLOADER_H

#include "Galogen46.h"

#include "Window/File.hpp"

#include "Shader/ShaderProgram.hpp"

#include "Scene/VertexBuffer.hpp"
#include "Scene/Mesh.hpp"
#include "Scene/Material.hpp"
#include "Scene/StaticMesh.hpp"
#include "Scene/Scene.hpp"


namespace J3
{
	class ModelLoader 
	{
		public:
			static void loadModel(File& file, Scene& scene);

			static VertexBuffer& loadArrayBuffer(GLvoid* data, GLenum type, size_t count, GLenum usage, GLuint attribIndex, GLuint componentCount, GLsizei stride = 0, GLvoid* offset = (GLvoid*) 0);
			static GLuint loadElementBuffer(unsigned int* data, unsigned int count, GLenum usage);
			static GLuint loadTexture(const char* path);
			static GLuint loadTexture(const char* path, GLint wrapS, GLint wrapT, GLint minFilter, GLint magFilter, bool generateMipMaps);

			static ShaderProgram* pbrShader;
	};

	class Loader
	{
		public:
			static void loadOBJ(File& file, Scene& scene);
	};
} // namespace J3

#endif // J3_MODELLOADER_H