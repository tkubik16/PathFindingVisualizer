#version 330 core
//in vec2 TexCoords;
out vec4 color;

//uniform sampler2D boxTex;
uniform vec3 boxColor;

void main()
{
	color = vec4(boxColor, 1.0);
}