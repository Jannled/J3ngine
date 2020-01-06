#include "lib/Galogen46.h"
#include "lib/glm/glm.hpp"

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

        glm::vec3 position = glm::vec3(2.0, 2.0, 2.0);
        glm::vec3 rotation;
        glm::vec3 scale;
};

#endif // MODEL_H