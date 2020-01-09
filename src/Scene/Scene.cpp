#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"

class Scene
{
    public:
        Scene();
        ~Scene();

        Camera getCamera();
};

#endif // SCENE_H