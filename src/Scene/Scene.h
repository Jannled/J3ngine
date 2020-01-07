#ifndef JSCENE_H
#define JSCENE_H

#include "lib/glm/glm.hpp"

class Scene 
{
    public:
        Scene();
        ~Scene();
    
    private:
        glm::vec3 cameraPosition;
        glm::vec3 cameraRotation;
};

#endif