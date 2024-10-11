#ifndef CONTENT_BOX_RENDERER_H
#define CONTENT_BOX_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"

class ContentBoxRenderer
{
public:
	ContentBoxRenderer(Shader& contentBoxShader, Shader& contentBoxOverflowHiddenShader);
	~ContentBoxRenderer();
	void DrawContentBox(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
	void DrawContentBox(Texture2D& texture, glm::vec2 position, bool wireframe, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
	void DrawContentBoxOverflowHidden(Texture2D& texture, glm::vec2 position, glm::vec2 size, glm::vec2 parentContentPosition, glm::vec2 parentContentSize, float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
	void DrawContentBoxOverflowHidden(Texture2D& texture, glm::vec2 position, glm::vec2 size, glm::vec2 parentContentPosition, glm::vec2 parentContentSize, float overflowRadius, glm::vec4 overflowTopCorners, glm::vec4 overflowBottomCorners, glm::vec4 borders, glm::vec2 screenSize, bool wireframe, float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
	void SetScreenWidth(int width);
	void SetScreenHeight(int height);
private:
	Shader contentBoxShader;
	Shader contentBoxOverflowHiddenShader;
	int screenWidth;
	int screenHeight;
	unsigned int quadVAO;
	void initRenderData();
};

#endif