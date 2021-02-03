#ifndef J3_STATICMESH_H
#define J3_STATICMESH_H

#include "Shader/ShaderProgram.hpp"

#include "SceneObject.hpp"
#include "Material.hpp"
#include "Mesh.hpp"

#ifndef UNIFORM_TRANSFORM
#define UNIFORM_TRANSFORM "transform"
#endif

#ifndef UNIFORM_MODELNORMAL
#define UNIFORM_MODELNORMAL "modelNormal"
#endif

#ifndef UNIFORM_MODELSPACE
#define UNIFORM_MODELSPACE "modelSpace"
#endif

namespace J3
{
	class StaticMesh : public SceneObject
	{
		public:
			StaticMesh(Mesh& mesh);
			~StaticMesh();

			void render(glm::mat4 viewProjection);
			void prepare(PBRMaterial& material);

		protected:
			Mesh& mesh;
	};
}


#endif // J3_STATICMESH_H