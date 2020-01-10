#include "Camera.h"

#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/matrix_transform.hpp"
#include "lib/glm/gtx/transform.hpp"

Camera::Camera(int width, int height)
{
    setResolution(width, height);
}

Camera::Camera(GLWindow::Point res)
{
    setResolution(res);
}

glm::mat4 Camera::viewProjection()
{
    return glm::perspective(glm::pi<float>() * 0.25f, aspectRatio, 0.1f, 100.f);
}

void Camera::setResolution(int width, int height)
{
    this->width = width;
    this->height = height;
    this->aspectRatio = width/height;
}

void Camera::setResolution(GLWindow::Point res)
{
    this->width = res.x;
    this->height = res.y;
    this->aspectRatio = width/height;
}

Camera::~Camera()
{

}