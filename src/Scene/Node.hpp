#ifndef J3_NODE_H
#define J3_NODE_H

#include <vector>

#include "Node.hpp"

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
			virtual ~Node();

			virtual void update();
			void parent(Node& node);
			void appendChild(Node& node);

			Node* getParent();

			// CLUDGE
			char* name;
			std::vector<Node> children;
		protected:
			Node* parentNode;
			
	};
}


#endif // J3_NODE_H