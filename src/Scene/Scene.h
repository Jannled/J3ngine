#ifndef JSCENE_H
#define JSCENE_H

#include "Camera.h"
#include "Model.h"
#include "Shader/ShaderProgram.h"

#include "lib/glm/glm.hpp"

#include <vector>

class Scene 
{
    public:
        Scene(Camera& camera);
        ~Scene();
    
        void render(ShaderProgram program);

        Camera* getCamera();

        bool loadToScene(const char* path);

    private:
        Camera* camera;
        std::vector<Model> models;
};

#endif