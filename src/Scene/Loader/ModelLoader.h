#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <vector>

#include "lib/Galogen46.h"

#include "Scene/Model.h"

class Loader
{
    static GLuint uploadMesh(Mesh& mesh);
    static bool loadOBJ(std::vector<Model> models);
}

#endif // MODEL_LOADER_H