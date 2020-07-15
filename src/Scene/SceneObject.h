#ifndef J3_SCENEOBJECT_H
#define J3_SCENEOBJECT_H

#include "Node.h"

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

namespace J3
{
	class SceneObject : protected Node
	{
		public:
			SceneObject();
			~SceneObject();

			void translate(glm::vec3 translation);
			void rotate(glm::vec3 rotation);
			void rotate(glm::quat rotation);
			void scale(glm::vec3 scale);

			void lookAt(glm::vec3 fokus, glm::vec3 up = glm::vec3(0.0, 1.0, 0.0));

			void update();

		protected:
			glm::vec3 position;
			glm::quat rotation;
			glm::vec3 scaling;
	};
}


#endif // J3_SCENEOBJECT_H