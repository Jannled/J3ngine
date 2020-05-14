#include "Camera.h"

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
    printf("I shouldN#t be here...\n");
    return projection() * view();
}

glm::mat4 Camera::view()
{
    return glm::translate(position) * glm::toMat4(rotation) * glm::scale(scale);
}

glm::mat4 Camera::projection()
{
    return glm::perspective(glm::pi<float>() * 0.25f, aspectRatio, 0.1f, 100.f);
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