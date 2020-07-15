#include "Camera.h"

using namespace J3;

Camera::Camera(unsigned int width, unsigned int height)
{
	setResolution(width, height);
}

glm::mat4 Camera::viewProjection()
{
	printf("I shouldN#t be here...\n");
	return projection() * view();
}

glm::mat4 Camera::view()
{
	return glm::translate(position) * glm::toMat4(rotation) * glm::scale(scaling);
}

glm::mat4 Camera::projection()
{
	return glm::perspective(glm::pi<float>() * 0.25f, aspectRatio, 0.1f, 100.f);
}

void Camera::setResolution(GLuint width, GLuint height)
{
	this->width = width;
	this->height = height;
	this->aspectRatio = (float) width/height;
}

Camera::~Camera()
{

}