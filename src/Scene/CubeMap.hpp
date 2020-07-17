#ifndef J3_CUBEMAP_H
#define J3_CUBEMAP_H

#include "Galogen46.h"

#include "Camera.hpp"
#include "Shader/ShaderProgram.hpp"

namespace J3
{
	class CubeMap
	{
		public:
			CubeMap(const char* path);
			virtual ~CubeMap();
			void renderCube();
			void renderQuad();
			void renderSkybox(Camera& camera);

			static ShaderProgram* equirectangularToCubemapShader;
			static ShaderProgram* irradianceShader;
			static ShaderProgram* backgroundShader;
			static ShaderProgram* prefilterShader;
			static ShaderProgram* brdfShader;

			GLuint getIrradianceMap();
			GLuint getPrefilterMap();
			GLuint getBRDFLUT();

		private:
			static GLuint cubeVAO;
			static GLuint cubeVBO;
			static GLuint quadVAO;
			static GLuint quadVBO;
			GLuint hdrTexture;
			GLuint irradianceMap;
			GLuint envCubemap;
			GLuint prefilterMap;
			GLuint brdfLUT;

			static void prepareCube();
			static void prepareQuad();
	};
}


#endif // J3_CUBEMAP_H