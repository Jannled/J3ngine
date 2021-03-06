#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, TexCoord);
	//FragColor = vec4(normal, 1.0f);
}