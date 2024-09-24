#version 330 core
in vec2 TexCoords;
in vec4 borders;
in vec4 ourPos;

out vec4 color;

uniform sampler2D image;
uniform vec3 boxColor;

void main()
{
	// borders(topY, bottomY, leftX, rightX);

	if(ourPos.x > borders.w || ourPos.y < borders.y || ourPos.x < borders.z || ourPos.y > borders.x){
		color = vec4(1.0, 1.0, 1.0, 0.0) * texture(image, TexCoords);
	}
	else
	{
		color = vec4(boxColor, 1.0) * texture(image, TexCoords);
	}

}