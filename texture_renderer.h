#ifndef TEXTURE_RENDERER_H
#define TEXTURE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"

class TextureRenderer
{
public:
	TextureRenderer(Shader& shader);
	~TextureRenderer();
	void Draw(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(80.0f, 60.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
	void Draw(Texture2D& texture, glm::vec2 position, bool wireframe, glm::vec2 size = glm::vec2(100.0f, 80.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
	void Draw(unsigned int texture, glm::vec2 position, glm::vec2 size = glm::vec2(1000.0f, 800.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
private:
	Shader shader;
	unsigned int quadVAO;
	void initRenderData();
};

#endif