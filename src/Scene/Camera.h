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

		void setPosition(glm::vec3 pos);
		void setPosition(float x, float y, float z);

	private:
		int width, height;
		float aspectRatio;
		glm::vec3 position = glm::vec3(0.0, 0.0, 3.0);
		glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);
		glm::vec3 fokus = glm::vec3(0.0, 0.0, 0.0);
};

#endif // CAMERA_H