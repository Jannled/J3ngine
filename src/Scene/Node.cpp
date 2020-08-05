class Camera;

#include "Node.hpp"

using namespace J3;

Node::Node()
{
	
}

Node::Node(char* name)
{
	this->name = name;
}

void Node::update()
{

}

void Node::parent(Node& node)
{
	node.children.push_back(node);
	this->parentNode = &node;
}

void Node::appendChild(Node& node)
{
	this->children.push_back(node);
	node.parentNode = &node;
}

Node::~Node()
{

}