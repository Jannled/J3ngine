#ifndef J3_CAMERA_H
#define J3_CAMERA_H

#include "SceneObject.hpp"

#include "Galogen46.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

namespace J3
{
	class Camera : public SceneObject
	{
		public:
			Camera(unsigned int widht, unsigned int height);
			~Camera();

			void setResolution(GLuint width, GLuint height);
			glm::mat4 view();
			glm::mat4 projection();
			glm::mat4 viewProjection();

		protected:
			GLuint width, height;
			float aspectRatio;
	};
}


#endif // J3_CAMERA_H