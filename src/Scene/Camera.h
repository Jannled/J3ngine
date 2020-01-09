#ifndef CAMERA_H
#define CAMERA_H

#include "lib/glm/glm.hpp"

class Camera
{
	public:
		Camera();
		~Camera();

		glm::mat4 viewProjection();
		void setResolution(int width, int height);

	private:
		int width, height;
		float aspectRatio;
};

#endif // CAMERA_H