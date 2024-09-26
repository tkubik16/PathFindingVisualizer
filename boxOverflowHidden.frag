#version 330 core
in vec2 TexCoords;
in vec4 borders;
in vec4 ourPos;

out vec4 color;

uniform sampler2D image;
uniform vec3 boxColor;

uniform vec2 topLeft;
uniform vec2 topRight;
uniform vec2 bottomLeft;
uniform vec2 bottomRight;
uniform vec2 screenSize;
uniform float radius;

void main()
{
	float pixelX = ((ourPos.x + 1) / 2) * screenSize.x;
	float pixelY = ((ourPos.y + 1) / 2) * screenSize.y;

	

	// borders(topY, bottomY, leftX, rightX);

	if(ourPos.x > borders.w || ourPos.y < borders.y || ourPos.x < borders.z || ourPos.y > borders.x){
		color = vec4(1.0, 1.0, 1.0, 0.0) * texture(image, TexCoords);
	}
	else if(ourPos.x < topLeft.x && ourPos.y > topLeft.y){
		float pixelTopLeftX = ((topLeft.x + 1) / 2) * screenSize.x;
		float pixelTopLeftY = ((topLeft.y + 1) / 2) * screenSize.y;

		float dist = distance(vec2(pixelX,pixelY), vec2(pixelTopLeftX,pixelTopLeftY));
		if(dist > radius){
			color = vec4(boxColor, 0.0) * texture(image, TexCoords);
		}
		else{
			color = vec4(boxColor, 1.0) * texture(image, TexCoords);
		}
		
	}
	else if(ourPos.x > topRight.x && ourPos.y > topRight.y){
		float pixelTopRightX = ((topRight.x + 1) / 2) * screenSize.x;
		float pixelTopRightY = ((topRight.y + 1) / 2) * screenSize.y;

		float dist = distance(vec2(pixelX,pixelY), vec2(pixelTopRightX,pixelTopRightY));
		if(dist > radius){
			color = vec4(boxColor, 0.0) * texture(image, TexCoords);
		}
		else{
			color = vec4(boxColor, 1.0) * texture(image, TexCoords);
		}
	}
	else if(ourPos.x < bottomLeft.x && ourPos.y < bottomLeft.y){
		float pixelBottomLeftX = ((bottomLeft.x + 1) / 2) * screenSize.x;
		float pixelBottomLeftY = ((bottomLeft.y + 1) / 2) * screenSize.y;

		float dist = distance(vec2(pixelX,pixelY), vec2(pixelBottomLeftX,pixelBottomLeftY));
		if(dist > radius){
			color = vec4(boxColor, 0.0) * texture(image, TexCoords);
		}
		else{
			color = vec4(boxColor, 1.0) * texture(image, TexCoords);
		}
	}
	else if(ourPos.x > bottomRight.x && ourPos.y < bottomRight.y){
		float pixelBottomRightX = ((bottomRight.x + 1) / 2) * screenSize.x;
		float pixelBottomRightY = ((bottomRight.y + 1) / 2) * screenSize.y;

		float dist = distance(vec2(pixelX,pixelY), vec2(pixelBottomRightX,pixelBottomRightY));
		if(dist > radius){
			color = vec4(boxColor, 0.0) * texture(image, TexCoords);
		}
		else{
			color = vec4(boxColor, 1.0) * texture(image, TexCoords);
		}
	}
	else
	{
		//color = vec4(boxColor, 1.0) * texture(image, TexCoords);
		color = vec4(boxColor, 1.0) * texture(image, TexCoords);
	}
	
	
}