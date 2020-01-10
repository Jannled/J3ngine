#ifndef CAMERA_H
#define CAMERA_H

#include "lib/glm/glm.hpp"
#include "AWindow/AWindow.h"

class Camera
{
	public:
		Camera(int width, int height);
		Camera(GLWindow::Point res);
		~Camera();

		glm::mat4 viewProjection();
		void setResolution(GLWindow::Point res);
		void setResolution(int width, int height);

	private:
		int width, height;
		float aspectRatio;
};

#endif // CAMERA_H