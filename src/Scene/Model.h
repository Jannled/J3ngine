#include "lib/Galogen46.h"

#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/quaternion.hpp"
#include "lib/glm/gtx/quaternion.hpp"

#include "Camera.h"
#include "Shader/ShaderProgram.h"

#ifndef MODEL_H
#define MODEL_H

#ifndef UNIFORM_TRANSFORM
#define UNIFORM_TRANSFORM "transform"
#endif

class Model
{
	public:
		Model(float vertices[], size_t cVertices, unsigned int indices[], size_t cIndices);
		virtual ~Model();

		void setPosition(float x, float y, float z);
		void setPosition(glm::vec3 pos);
		void setEulerRotation(float x, float y, float z);
		void setEulerRotation(glm::vec3 rot);

		void render(ShaderProgram &shaderProgram, Camera &cam);

	private:
		size_t cVertices;
		size_t cIndices;

		GLuint VAO;
		GLuint VBO;
		GLuint EBO;

		glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
		glm::quat rotation = glm::quat(glm::vec3(0.0, 0.0, 0.0));
		glm::vec3 scale = glm::vec3(0.5, 0.5, 0.5);
};

#endif // MODEL_H