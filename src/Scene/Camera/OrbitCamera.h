#ifndef ORBIT_CAMERA_H
#define ORBIT_CAMERA_H

#include "Camera.h"

class OrbitCamera : public Camera 
{
	public: 
		OrbitCamera(int width, int height, float distance = 10);
		OrbitCamera(GLWindow::Point res, float distance = 10);
		virtual ~OrbitCamera();

		virtual glm::mat4 viewProjection();
		virtual glm::mat4 view();
	private:
		float distance;
};

#endif // ORBIT_CAMERA_H