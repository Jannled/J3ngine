#ifndef CAMERA_H
#define CAMERA_H

#include "Node.h"

#include "lib/glm/glm.hpp"
#include "AWindow/AWindow.h"

class Camera : public Node
{
	public:
		Camera(int width, int height);
		Camera(GLWindow::Point res);
		virtual ~Camera();

		glm::mat4 viewProjection();
		void setResolution(GLWindow::Point res);
		void setResolution(int width, int height);

	private:
		int width, height;
		float aspectRatio;
		
		glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);
		glm::vec3 fokus = glm::vec3(0.0, 0.0, 0.0);
};

#endif // CAMERA_H