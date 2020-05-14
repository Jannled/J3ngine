#ifndef LOOK_CAMERA_H
#define LOOK_CAMERA_H

#include "Camera.h"

class LookCamera : public Camera 
{
	public: 
		LookCamera(int width, int height);
		LookCamera(GLWindow::Point res);
		virtual ~LookCamera();

		virtual glm::mat4 viewProjection();
		virtual glm::mat4 view();

	private:
		glm::vec3 up;
		glm::vec3 fokus;
};

#endif // LOOK_CAMERA_H