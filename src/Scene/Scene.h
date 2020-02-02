#ifndef JSCENE_H
#define JSCENE_H

#include "Model.h"
#include "Camera.h"
#include "CubeMap.h"
#include "Shader/ShaderProgram.h"

#include "AWindow/File.h"

#include "lib/glm/glm.hpp"

#include <vector>

class Scene 
{
    public:
        Scene(Camera& camera, CubeMap& cubemap);
        ~Scene();
    
        void update();
        void render(ShaderProgram program);

        Camera* getCamera();

        bool loadToScene(File& path);

    private:
        Camera* camera;
        CubeMap* cubemap;
        std::vector<Model> models;
};

#endif