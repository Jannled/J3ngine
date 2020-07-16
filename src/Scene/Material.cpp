#include "Material.h"

using namespace J3;

Material::Material(ShaderProgram& shaderProgram) : shaderProgram(shaderProgram)
{
    
}
    
Material::~Material()
{
    // TODO Free up Material
}