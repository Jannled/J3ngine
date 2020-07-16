#ifndef J3_MATERIAL_H
#define J3_MATERIAL_H

#include "Shader/ShaderProgram.h"

namespace J3
{
	class Material
	{
		public:
			Material(ShaderProgram& shaderProgram);
			~Material();

			void prepare();

		protected:
			ShaderProgram& shaderProgram;
	};
}


#endif // J3_MATERIAL_H