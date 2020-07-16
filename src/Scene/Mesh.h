#ifndef J3_MESH_H
#define J3_MESH_H

#include "Material.h"

namespace J3
{
	class Mesh
	{
		public:
			Mesh();
			Mesh(Material* material);
			~Mesh();

        protected:
			Material* material;
	};
}


#endif // J3_MESH_H