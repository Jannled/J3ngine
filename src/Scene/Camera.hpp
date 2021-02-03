#ifndef J3_CAMERA_H
#define J3_CAMERA_H

#include "SceneObject.hpp"

#include "Galogen46.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

#define CPLANE_NEAR   0.1f
#define CPLANE_FAR  100.0f

namespace J3
{
	class Camera : public SceneObject
	{
		public:
			Camera(unsigned int width, unsigned int height, float cnear = CPLANE_NEAR, float cfar = CPLANE_FAR);
			~Camera();

			void setResolution(GLuint width, GLuint height, float cnear = CPLANE_NEAR, float cfar = CPLANE_FAR);
			void setClipping(float cnear = 0.1f, float cfar = 100.0f);
			glm::mat4 view();
			glm::mat4 projection();
			glm::mat4 viewProjection();

			void translate(glm::vec3 translation);
			void rotate(glm::vec3 rotation);
			void rotate(glm::quat rotation);
			void scale(glm::vec3 scale);
			void lookAt(glm::vec3 direction, glm::vec3 up);
			void lookAt(glm::vec3 position, glm::vec3 direction, glm::vec3 up);
			
			void calcView();
		protected:
			GLuint width, height;
			glm::mat4 viewMat;
			glm::mat4 projectionMat;
			float aspectRatio;
	};
}


#endif // J3_CAMERA_H