#include "Camera.h"

#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/matrix_transform.hpp"
#include "lib/glm/gtx/transform.hpp"

#include <stdio.h>

Camera::Camera(int width, int height)
    : Node(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f))
{
    setResolution(width, height);
}

Camera::Camera(GLWindow::Point res)
    : Node(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f))
{
    setResolution(res);
}

glm::mat4 Camera::viewProjection()
{
    return glm::perspective(glm::pi<float>() * 0.25f, aspectRatio, 0.1f, 100.f) * glm::lookAt(position, fokus, up);
}

void Camera::setResolution(int width, int height)
{
    this->width = width;
    this->height = height;
    this->aspectRatio = (float) width/height;
}

void Camera::setResolution(GLWindow::Point res)
{
    setResolution(res.x, res.y);
}

Camera::~Camera()
{

}