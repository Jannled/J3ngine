#ifndef J3_SCENE_H
#define J3_SCENE_H

#include "Camera.hpp"
#include "CubeMap.hpp"
#include "StaticMesh.hpp"

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

			void setResolution(GLuint width, GLuint height);

		private:
			std::vector<StaticMesh> renderTargets;
			Node* rootNode;
			Camera& camera;
			CubeMap* cubeMap = NULL;
	};
}

#endif // J3_SCENE_H