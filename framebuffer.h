#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Framebuffer
{
public:
	unsigned int fbo;
	unsigned int texture;
	int screenWidth;
	int screenHeight;
	// constructors and destructors
	Framebuffer(int width, int height);
	~Framebuffer();
	// methods
	void Init();
	void UpdateScreenSize(int width, int height);
	void Bind();
	void Unbind();

};

#endif