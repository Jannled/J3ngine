#ifndef J3_SCENEOBJECT_H
#define J3_SCENEOBJECT_H

#include "Node.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

namespace J3
{
	class SceneObject : public Node
	{
		public:
			SceneObject(glm::vec3 loc = glm::vec3(0.0, 0.0, 0.0), glm::quat rot = glm::quat(1.0, 0.0, 0.0, 0.0), glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0));
			~SceneObject();

			void translate(glm::vec3 translation);
			void rotate(glm::vec3 rotation);
			void rotate(glm::quat rotation);
			void scale(glm::vec3 scale);

			void lookAt(glm::vec3 fokus, glm::vec3 up = glm::vec3(0.0, 1.0, 0.0));

			void update();

			// TODO not sure if they should be public or protected
			glm::vec3 position;
			glm::quat rotation;
			glm::vec3 scaling;

		protected:
			
	};
}


#endif // J3_SCENEOBJECT_H