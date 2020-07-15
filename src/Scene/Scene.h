#ifndef J3_SCENE_H
#define J3_SCENE_H

#include "Camera.h"
#include "CubeMap.h"

#include <vector>

namespace J3
{
	class Scene
	{
		public:
			Scene();
			~Scene();

			void update();
			void render();

		private:
			std::vector<Node> nodes;
			Camera* camera;
			CubeMap* cubeMap;
	};
}


#endif // J3_SCENE_H