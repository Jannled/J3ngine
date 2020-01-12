#ifndef JSCENE_H
#define JSCENE_H

#include "lib/glm/glm.hpp"
#include "Camera.h"
#include "Model.h"

class Scene 
{
    public:
        Scene();
        ~Scene();
    
        Camera* getCamera();

        static Model* loadScene(const char* path);

    private:
        Camera* camera;
};

#endif