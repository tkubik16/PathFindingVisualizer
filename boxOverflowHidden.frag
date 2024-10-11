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

uniform vec4 overflowTopCorners;
uniform vec4 overflowBottomCorners;
uniform float overflowRadius;

void main()
{
	float pixelX = ((ourPos.x + 1) / 2) * screenSize.x;
	float pixelY = ((ourPos.y + 1) / 2) * screenSize.y;

	vec2 overflowTopLeft = overflowTopCorners.xy;
	vec2 overflowTopRight = overflowTopCorners.zw;
	vec2 overflowBottomLeft = overflowBottomCorners.xy;
	vec2 overflowBottomRight = overflowBottomCorners.zw;
	

	// borders(topY, bottomY, leftX, rightX);

	if(ourPos.x > borders.w || ourPos.y < borders.y || ourPos.x < borders.z || ourPos.y > borders.x){
		color = vec4(1.0, 1.0, 1.0, 0.0) * texture(image, TexCoords);
	}
	else if(ourPos.x < overflowTopLeft.x && ourPos.y > overflowTopLeft.y){
		float pixelOverflowTopLeftX = ((overflowTopLeft.x + 1) / 2) * screenSize.x;
		float pixelOverflowTopLeftY = ((overflowTopLeft.y + 1) / 2) * screenSize.y;

		float dist = distance(vec2(pixelX,pixelY), vec2(pixelOverflowTopLeftX,pixelOverflowTopLeftY));
		if(dist > overflowRadius){
			color = vec4(boxColor, 0.0) * texture(image, TexCoords);
		}
		else{
			color = vec4(boxColor, 1.0) * texture(image, TexCoords);
		}
	}
	else if(ourPos.x > overflowTopRight.x && ourPos.y > overflowTopRight.y){
		float pixelOverflowTopRightX = ((overflowTopRight.x + 1) / 2) * screenSize.x;
		float pixelOverflowTopRightY = ((overflowTopRight.y + 1) / 2) * screenSize.y;

		float dist = distance(vec2(pixelX,pixelY), vec2(pixelOverflowTopRightX,pixelOverflowTopRightY));
		if(dist > overflowRadius){
			color = vec4(boxColor, 0.0) * texture(image, TexCoords);
		}
		else{
			color = vec4(boxColor, 1.0) * texture(image, TexCoords);
		}
	}
	else if(ourPos.x < overflowBottomLeft.x && ourPos.y < overflowBottomLeft.y){
		float pixelOverflowBottomLeftX = ((overflowBottomLeft.x + 1) / 2) * screenSize.x;
		float pixelOverflowBottomLeftY = ((overflowBottomLeft.y + 1) / 2) * screenSize.y;

		float dist = distance(vec2(pixelX,pixelY), vec2(pixelOverflowBottomLeftX,pixelOverflowBottomLeftY));
		if(dist > overflowRadius){
			color = vec4(boxColor, 0.0) * texture(image, TexCoords);
		}
		else{
			color = vec4(boxColor, 1.0) * texture(image, TexCoords);
		}
	}
	else if(ourPos.x > overflowBottomRight.x && ourPos.y < overflowBottomRight.y){
		float pixelOverflowBottomRightX = ((overflowBottomRight.x + 1) / 2) * screenSize.x;
		float pixelOverflowBottomRightY = ((overflowBottomRight.y + 1) / 2) * screenSize.y;

		float dist = distance(vec2(pixelX,pixelY), vec2(pixelOverflowBottomRightX,pixelOverflowBottomRightY));
		if(dist > overflowRadius){
			color = vec4(boxColor, 0.0) * texture(image, TexCoords);
		}
		else{
			color = vec4(boxColor, 1.0) * texture(image, TexCoords);
		}
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