#ifndef BOX_RENDERER_H
#define BOX_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"

class BoxRenderer
{
public:
	BoxRenderer(Shader& boxShader, Shader& boxOverflowHiddenShader);
	~BoxRenderer();
	void DrawBox(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
	void DrawBoxOverflowHidden(Texture2D& texture, glm::vec2 position, glm::vec2 size, glm::vec2 parentContentPosition, glm::vec2 parentContentSize, float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
	void SetScreenWidth(int width);
	void SetScreenHeight(int height);
private:
	Shader boxShader;
	Shader boxOverflowHiddenShader;
	int screenWidth;
	int screenHeight;
	unsigned int quadVAO;
	void initRenderData();
};

#endif