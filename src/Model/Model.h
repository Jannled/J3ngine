#include "lib/Galogen46.h"

#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/quaternion.hpp"
#include "lib/glm/gtx/quaternion.hpp"

#include "Shader/ShaderProgram.h"

#ifndef MODEL_H
#define MODEL_H

class Model
{
    public:
        Model(float vertices[], size_t cVertices, unsigned int indices[], size_t cIndices);
        virtual ~Model();

        void render(ShaderProgram &shaderProgram);

    private:
        size_t cVertices;
        size_t cIndices;

        GLuint VAO;
        GLuint VBO;
        GLuint EBO;

        glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
        glm::quat rotation = glm::quat(glm::vec3(0.0, 45.0, 45.0));
        glm::vec3 scale = glm::vec3(0.5, 0.5, 0.5);
};

#endif // MODEL_H