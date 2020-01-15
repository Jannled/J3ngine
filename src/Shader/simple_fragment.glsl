#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	FragColor = vec4(normal, 1.0f);
}