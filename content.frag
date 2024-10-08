#version 330 core
in vec2 TexCoords;
in vec4 ourPos;
out vec4 color;

uniform sampler2D image;
uniform vec3 boxColor;

void main()
{
	color = vec4(boxColor, 1.0) * texture(image, TexCoords);

}