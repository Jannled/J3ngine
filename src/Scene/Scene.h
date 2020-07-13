#ifndef J3_SCENE_H
#define J3_SCENE_H

#include "Camera.h"
#include "CubeMap.h"

namespace J3
{
	class Scene
	{
		public:
			Scene();
			~Scene();

			void render();

		private:
			Camera* camera;
			CubeMap* cubeMap;
	};
}


#endif // J3_SCENE_H