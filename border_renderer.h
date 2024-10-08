#ifndef BORDER_RENDERER_H
#define BORDER_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"

class BorderRenderer
{
public:
	BorderRenderer(Shader& borderShader, Shader& borderOverflowHiddenShader);
	~BorderRenderer();
	void DrawBox(Texture2D& texture, glm::vec2 borderPosition, glm::vec2 borderSize, glm::vec2 topLeft, glm::vec2 topRight, glm::vec2 bottomLeft, glm::vec2 bottomRight, float radius, glm::vec2 screenSize, float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
	void DrawBoxOverflowHidden(Texture2D& texture, glm::vec2 borderPosition, glm::vec2 borderSize, glm::vec2 parentContentPosition, glm::vec2 parentContentSize, glm::vec4 borders, glm::vec2 topLeft, glm::vec2 topRight, glm::vec2 bottomLeft, glm::vec2 bottomRight, float radius, glm::vec2 screenSize, float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
	void SetScreenWidth(int width);
	void SetScreenHeight(int height);
private:
	Shader borderShader;
	Shader borderOverflowHiddenShader;
	int screenWidth;
	int screenHeight;
	unsigned int quadVAO;
	void initRenderData();
};

#endif