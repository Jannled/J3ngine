#ifndef J3_SHADERPROGRAM_H
#define J3_SHADERPROGRAM_H

#include "Galogen46.h"
#include "glm/glm.hpp"

#include "Shader.hpp"

namespace J3
{
	class ShaderProgram
	{
		public:
			ShaderProgram(Shader &vertexShader, Shader &fragmentShader);
			ShaderProgram(const char* vertexShader, const char* fragmentShader);
			~ShaderProgram();

			void init(Shader &vertexShader, Shader &fragmentShader);

			void link();
			void use();

			GLint getUniformLocation(const char* name);

			void setBool(const char* name, bool value);
			void setInt(const char* name, int value);
			void setFloat(const char* name, float value);

			void setVec3f(const char* name, float* value);
			void setVec3f(const char* name, glm::vec3 value);

			void setMat3f(const char* name, glm::mat3 value);
			
			void setMat4f(const char* name, float *value, GLboolean transpose);
			void setMat4f(const char* name, glm::mat4 value);

			const GLuint programID;

		private:
			Shader* shaders;
			size_t shaderCount = 2;
	};
}


#endif // J3_SHADERPROGRAM_H