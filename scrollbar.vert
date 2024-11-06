#version 330 core
layout (location = 0) in vec4 vertex;

out vec2 TexCoords;
out vec4 ourPos;

uniform mat4 model;
// no view matrix because it will never change so we basically have an identity view matrix
uniform mat4 projection;
uniform mat4 view;

void main()
{
	TexCoords = vertex.zw;
	
	ourPos = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
	gl_Position = ourPos;
}