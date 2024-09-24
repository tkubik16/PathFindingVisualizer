#version 330 core
layout (location = 0) in vec4 vertex;

out vec2 TexCoords;
//out vec2 BoundingTopLeft;
//out vec2 BoundingBottomRight;
out vec4 ourPos;



out vec4 borders;

uniform mat4 model;
// no view matrix because it will never change so we basically have an identity view matrix
uniform mat4 projection;
uniform mat4 view;

//uniform vec2 parentContentPosition;
//uniform vec2 parentContentSize;
uniform vec4 boundaries;

uniform vec2 screenSize;

void main()
{
	TexCoords = vertex.zw;
	
	borders = boundaries;


	ourPos = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
	gl_Position = ourPos;
}