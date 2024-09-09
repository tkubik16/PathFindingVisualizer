#version 330 core
layout (location = 0) in vec4 vertex;

//out vec2 TexCoords;

uniform mat4 model;
// no view matrix because it will never change so we basically have an identity view matrix
uniform mat4 projection;

void main()
{
	//TexCoords = vertex.zw;
	gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}