#include "LookCamera.h"

#include <cstdio>

LookCamera::LookCamera(int width, int height) : Camera(width, height)
{
	up = glm::vec3(0.0, 1.0, 0.0);
	fokus = glm::vec3(0.0, 0.0, 0.0);
}

LookCamera:: LookCamera(GLWindow::Point res) : Camera(res)
{
	up = glm::vec3(0.0, 1.0, 0.0);
	fokus = glm::vec3(0.0, 0.0, 0.0);
}

LookCamera::~LookCamera()
{

}

glm::mat4 LookCamera::viewProjection()
{
	return projection() * view();
}

glm::mat4 LookCamera::view()
{
	return glm::lookAt(position, fokus, up);
}