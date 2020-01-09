#include "Camera.h"

#include "lib/glm/gtc/matrix_transform.hpp"
#include "lib/glm/gtx/transform.hpp"

Camera::Camera()
{

}

glm::mat4 Camera::viewProjection()
{
    return glm::perspective((float) glm::radians(45.0), aspectRatio, 0.1f, 100.0f);
}

Camera::~Camera()
{

}