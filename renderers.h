#ifndef RENDERERS_H
#define RENDERERS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "box_renderer.h"
#include "content_box_renderer.h"
#include "texture_renderer.h"

class Renderers 
{
public:
	BoxRenderer* boxRenderer;
	ContentBoxRenderer* contentBoxRenderer;
	TextureRenderer* textureRenderer;
	// constructor and destructor
	Renderers();
	~Renderers();
	// methods
	void SetScreenSize(int width, int height);
	void SetScreenWidth(int width);
	void SetScreenHeight(int height);
private:
	int screenWidth;
	int screenHeight;
};

#endif