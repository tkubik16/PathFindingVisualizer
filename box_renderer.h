#ifndef BOX_RENDERER_H
#define BOX_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"
#include "element.h"

class BoxRenderer
{
public:
	BoxRenderer(Shader& shader);
	~BoxRenderer();
	void DrawBox(glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color);
	void DrawBox(Element* element);
private:
	Shader shader;
	unsigned int quadVAO;
	void initRenderData();
};

#endif