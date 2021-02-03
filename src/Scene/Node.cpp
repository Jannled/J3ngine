class Camera;

#include "Node.hpp"

using namespace J3;

Node::Node()
{
	children = std::vector<Node>();
	name = "";
}

Node::Node(const char* name)
{
	this->name = name;
	children = std::vector<Node>();
}

void Node::update()
{
	// Do Update stuff

	// Update children
	for(Node& node : children)
	{
		node.update();
	}
}

/*void Node::parent(Node& node)
{
	node.children.push_back(node);
	this->parentNode = &node;
}

void Node::appendChild(Node& node)
{
	this->children.push_back(node);
	node.parentNode = this;
}*/

Node::~Node()
{

}