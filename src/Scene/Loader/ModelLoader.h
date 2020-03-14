#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <vector>

#include "lib/Galogen46.h"

#include "Scene/Model.h"
#include "AWindow/File.h"

class Loader
{
    public:
        static bool uploadMesh(Mesh& mesh);
        static bool loadOBJ(File& file, std::vector<Model>& models);
};

#endif // MODEL_LOADER_H