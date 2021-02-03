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

			void appendChild(Node& node, Node& appendTo);
			void appendChild(Node& node);
			void appendChild(StaticMesh& node, Node& appendTo);
			void appendChild(StaticMesh& node);

			CubeMap* cubeMap = NULL;
			Camera& camera;

		private:
			std::vector<StaticMesh> renderTargets;
			Node* rootNode;
			
	};
}

#endif // J3_SCENE_H