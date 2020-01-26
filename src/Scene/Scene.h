#ifndef JSCENE_H
#define JSCENE_H

#include "Model.h"
#include "Camera.h"
#include "CubeMap.h"
#include "Shader/ShaderProgram.h"

#include "lib/glm/glm.hpp"

#include <vector>

class Scene 
{
    public:
        Scene(Camera& camera, CubeMap& cubemap);
        ~Scene();
    
        void render(ShaderProgram program);

        Camera* getCamera();

        bool loadToScene(const char* path);
        bool loadToScene(const char* path, const char* baseDir);

    private:
        Camera* camera;
        CubeMap* cubemap;
        std::vector<Model> models;
};

#endif