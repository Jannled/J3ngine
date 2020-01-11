#ifndef JSCENE_H
#define JSCENE_H

#include "lib/glm/glm.hpp"
#include "Scene/Camera.h"

class Scene 
{
    public:
        Scene();
        ~Scene();
    
        Camera* getCamera();

        static int loadScene(const char* path);

    private:
        Camera* camera;
};

#endif