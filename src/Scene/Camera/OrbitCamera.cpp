#include "OrbitCamera.h"

OrbitCamera::OrbitCamera(int width, int height, float distance) : Camera(width, height)
{
	this->distance = distance;
}

OrbitCamera:: OrbitCamera(GLWindow::Point res, float distance) : Camera(res)
{
	this->distance = distance;
}

OrbitCamera::~OrbitCamera()
{

}

glm::mat4 OrbitCamera::viewProjection()
{
	return projection() * view();
}

glm::mat4 OrbitCamera::view()
{
	return glm::translate(glm::vec3(0.0, 0.0, -distance)) * glm::translate(position) * glm::toMat4(rotation);
}