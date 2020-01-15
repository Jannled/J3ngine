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

#ifndef UNIFORM_MODELNORMAL
#define UNIFORM_MODELNORMAL "modelNormal"
#endif

typedef struct
{
	GLuint VERTICES;
	GLuint cVertices;

	GLuint NORMALS;
	GLuint cNormals;

	GLuint TEXCOORDS;
	GLuint cTexcoords;

	GLuint INDICES;
	GLuint cIndices;

	GLuint TEX0;

	GLuint VAO;
} GLData;

class Model
{
	public:
		Model(float vertices[], size_t cVertices, unsigned int indices[], size_t cIndices);
		Model(GLData data);
		virtual ~Model();

		void setPosition(float x, float y, float z);
		void setPosition(glm::vec3 pos);
		void setEulerRotation(float x, float y, float z);
		void setEulerRotation(glm::vec3 rot);

		void render(ShaderProgram &shaderProgram, Camera &cam);

		static GLuint loadTexture(char const * path);

	private:
		GLData glData;

		glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
		glm::quat rotation = glm::quat(glm::vec3(0.0, 0.0, 0.0));
		glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
};

#endif // MODEL_H