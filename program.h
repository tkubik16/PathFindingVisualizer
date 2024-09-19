#ifndef PROGRAM_H
#define PROGRAM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "document.h"
#include "renderers.h"
#include "framebuffer.h"

class Program
{
public:
	Document Doc;
	bool Keys[1024];
	bool KeysProcessed[1024];
	int screenWidth, screenHeight;
	glm::mat4 projection;
	glm::mat4 view;
	float scrollDist;
	Renderers* renderers;
	// constructor/destructor
	Program(int width, int height);
	~Program();
	// initialize program state (load all shaders/textures/etc.)
	void Init();
	// program loop
	void ProcessInput(float dt);
	void Update(float dt);
	void Update();
	void Render();
	void UpdateScreenSize(int width, int height);
	

};

#endif