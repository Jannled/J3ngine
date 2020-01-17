#include "Node.h"

Node::Node(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{
    this->position = pos;
    setEulerRotation(rot);
    this->scale = scale;
}

Node::Node(glm::vec3 pos, glm::quat rot, glm::vec3 scale)
{
    this->position = pos;
    this->rotation = rot;
    this->scale = scale;
}

glm::vec3* Node::getPosition()
{
    return &position;
}

void Node::setPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Node::setPosition(glm::vec3 pos)
{
	this->position = pos;
}

void Node::setEulerRotation(float x, float y, float z)
{
	rotation = glm::quat(glm::vec3(x, y, z));
}

void Node::setEulerRotation(glm::vec3 rot)
{
	rotation = glm::quat(rot);
}

Node::~Node()
{
    
}