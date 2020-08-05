#ifndef J3_SHADER_H
#define J3_SHADER_H

#include "Galogen46.h"

namespace J3
{
	class Shader
	{
		public:
			Shader(const char* code, GLenum type);
			~Shader();

			GLint compile();
			GLint isCompiled();

			const GLuint handle;
			const GLenum type;
	};
}


#endif // J3_SHADER_H