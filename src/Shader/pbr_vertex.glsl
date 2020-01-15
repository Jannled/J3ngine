#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

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
    Normal = modelNormal * aNormal;

    gl_Position = transform * vec4(aPos, 1.0);
}