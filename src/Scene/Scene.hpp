#ifndef J3_SCENE_H
#define J3_SCENE_H

#include "Camera.hpp"
#include "CubeMap.hpp"

#include <vector>

namespace J3
{
	class Scene
	{
		public:
			Scene(Camera& camera);
			~Scene();

			void update();
			void render();

		private:
			std::vector<Node> nodes;
			Camera& camera;
			CubeMap* cubeMap;
	};
}

#endif // J3_SCENE_H