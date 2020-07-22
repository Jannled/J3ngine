#ifndef J3_STATICMESH_H
#define J3_STATICMESH_H

#include "SceneObject.hpp"
#include "Material.hpp"
#include "Mesh.hpp"

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