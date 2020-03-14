#include "ModelLoader.h"

#include <stdio.h>

bool Loader::uploadMesh(Mesh& mesh)
{
    if(!Model::loadArrayBuffer(mesh.vertices))
    {
        printf("Error while uploading %d Vertices to the GPU!", mesh.vertices.dataLength);
        return false;
    }
    if(!Model::loadArrayBuffer(mesh.normals))
    {
        printf("Error while uploading %d Normals to the GPU!", mesh.normals.dataLength);
        return false;
    }
    if(!Model::loadArrayBuffer(mesh.texCoords))
    {
        printf("Error while uploading %d UVs to the GPU!", mesh.texCoords.dataLength);
        return false;
    }
    return true;
}