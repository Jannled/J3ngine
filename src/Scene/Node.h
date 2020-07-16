#ifndef J3_NODE_H
#define J3_NODE_H

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

namespace J3
{
	class Node
	{
		public:
			Node();
			Node(char* name);
			~Node();

			void parent(Node& node);
			void appendChild(Node& node);

			char* name;

		protected:
			Node* parentNode;
			std::vector<Node> children;
	};
}


#endif // J3_NODE_H