#include "lib/Galogen46.h"

#ifndef MODEL_H
#define MODEL_H

class Model
{
    public:
        Model(float vertices[], size_t cVertices, unsigned int indices[], size_t cIndices);
        virtual ~Model();

        void render();

    private:
        size_t cVertices;
        size_t cIndices;

        GLuint VAO;
        GLuint VBO;
        GLuint EBO;
};

#endif // MODEL_H