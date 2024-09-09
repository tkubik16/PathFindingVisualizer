#include <iostream>

#include "program.h"
#include "box_renderer.h"
#include "resource_manager.h"

BoxRenderer* boxRenderer;

Program::Program(int width, int height) : Doc(width, height), Width(width), Height(height), Keys(), KeysProcessed()
{

}

Program::~Program()
{
	delete boxRenderer;
}

void Program::Init()
{
	// load shaders
	ResourceManager::LoadShader("box.vert", "box.frag", nullptr, "boxshader");
	// configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("boxshader").SetMatrix4("projection", projection);

	boxRenderer = new BoxRenderer(ResourceManager::GetShader("boxshader"));

	this->Doc.root->PrintInfo();

}

void Program::ProcessInput(float dt)
{

}

void Program::Update(float dt)
{

}

void Program::Render()
{

}

