#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 WorldPos;
out vec3 Normal;

uniform mat4 transform;
uniform mat4 modelSpace;
uniform mat3 modelNormal;

void main()
{
    TexCoords = aTexCoords;
    WorldPos = vec3(modelSpace * vec4(aPos, 1.0));
    Normal = mat3(modelSpace) * aNormal;   

    gl_Position =  transform * vec4(aPos, 1.0);
}