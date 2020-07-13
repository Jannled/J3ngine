#ifndef J3_NODE_H
#define J3_NODE_H

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

namespace J3
{
	class Node
	{
		public:
			Node();
			~Node();

			void translate(glm::vec3 translation);
			void rotate(glm::vec3 rotation);
			void scale(glm::vec3 scale);

			void lookAt(glm::vec3 pos, glm::vec3 up = glm::vec3(0.0, 1.0, 0.0));

			void update();

		private:
			glm::vec3 position;
			glm::quat rotation;
			glm::vec3 scaling;
	};
}


#endif // J3_NODE_H