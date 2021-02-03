#include "SceneObject.hpp"

using namespace J3;

SceneObject::SceneObject(glm::vec3 loc, glm::quat rot, glm::vec3 scale)
{
	this->position = loc;
	this->rotation = rot;
	this->scaling = scale;
}

void SceneObject::translate(glm::vec3 translation)
{
	this->position += translation;
}

void SceneObject::rotate(glm::vec3 rotation)
{
	rotate(glm::quat(rotation));
}

void SceneObject::rotate(glm::quat rotation)
{
	this->rotation += rotation;
	//glm::toMat4(rotation); ???
}

void SceneObject::scale(glm::vec3 scale)
{
	this->scaling *= scale;
}

void SceneObject::lookAt(glm::vec3 fokus, glm::vec3 up)
{
	// TODO Magic calculation for look at
}

void SceneObject::update()
{

}

SceneObject::~SceneObject()
{

}