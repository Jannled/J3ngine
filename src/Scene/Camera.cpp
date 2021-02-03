#include "Camera.hpp"

using namespace J3;

Camera::Camera(unsigned int width, unsigned int height, float cnear, float cfar)
{
	setResolution(width, height, cnear, cfar);
}

glm::mat4 Camera::viewProjection()
{
	return projection() * view();
}

glm::mat4 Camera::view()
{
	return viewMat;
}

glm::mat4 Camera::projection()
{
	return projectionMat;
}

void Camera::translate(glm::vec3 translation) 
{
	SceneObject::translate(translation);
	calcView();
}

void Camera::rotate(glm::vec3 rotation) 
{
	SceneObject::rotate(rotation);
	calcView();
}

void Camera::rotate(glm::quat rotation) 
{
	SceneObject::rotate(rotation);
	calcView();
}

void Camera::scale(glm::vec3 scale) 
{
	SceneObject::scale(scale);
	calcView();
}

void Camera::lookAt(glm::vec3 direction, glm::vec3 up)
{
	rotation = glm::quatLookAt(glm::normalize(direction - position), up);
	calcView();
}

void Camera::lookAt(glm::vec3 position, glm::vec3 direction, glm::vec3 up)
{
	//viewMat = glm::lookAt(position, direction, up);
	this->position = position;
	lookAt(direction, up);
}

void Camera::setResolution(GLuint width, GLuint height, float cnear, float cfar)
{
	this->width = width;
	this->height = height;
	this->aspectRatio = (float) width/height;

	projectionMat = glm::perspective(glm::pi<float>() * 0.25f, aspectRatio, cnear, cfar);
}

void Camera::setClipping(float cnear, float cfar)
{
	setResolution(width, height, cnear, cfar);
}

void Camera::calcView()
{
	viewMat = glm::translate(position) * glm::toMat4(rotation) * glm::scale(scaling);
}

Camera::~Camera()
{

}