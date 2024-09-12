#include <iostream>

#include "program.h"
#include "box_renderer.h"
#include "resource_manager.h"
#include "element.h"

BoxRenderer* boxRenderer;

Program::Program(int width, int height) : Doc(width, height), screenWidth(width), screenHeight(height), Keys(), KeysProcessed(), scrollDist(0.0f)
{

}

Program::~Program()
{
	delete boxRenderer;
}

void Program::Init()
{
	//configure projection and view
	this->projection = glm::ortho(0.0f, static_cast<float>(this->screenWidth), static_cast<float>(this->screenHeight), 0.0f, -1.0f, 1.0f);
	glm::vec2 midOffset = glm::vec2(this->Doc.screenWidth * 0.5f, this->Doc.screenHeight * 0.5f);
	view = glm::translate(view, glm::vec3(0.0f, scrollDist, 0.0f));

	// load shaders
	ResourceManager::LoadShader("box.vert", "box.frag", nullptr, "boxshader");
	// configure shaders
	ResourceManager::GetShader("boxshader").Use().SetInteger("image", 0);
	ResourceManager::GetShader("boxshader").SetMatrix4("projection", this->projection);
	ResourceManager::GetShader("boxshader").SetMatrix4("view", this->view);

	// load textures
	ResourceManager::LoadTexture("textures/block.png", false, "block");
	ResourceManager::LoadTexture("textures/background.jpg", false, "background");
	ResourceManager::LoadTexture("textures/no_tex.png", false, "no_tex");

	boxRenderer = new BoxRenderer(ResourceManager::GetShader("boxshader"));

	Element* firstEl = this->Doc.AddElement("firstEl");
	firstEl->parent = this->Doc.root;

	// below here create doc tree maybe
	this->Doc.Init();
	this->Doc.root->PrintInfo();
	

	firstEl->boxModel.SetSize(100, 100);
	firstEl->boxModel.SetMarginAll(50);
	//this->Doc.root->CalculatePositions();
	//this->Doc.root->CalculateSize();

	//firstEl->CalculateSize();
	//firstEl->CalculatePositions();
	

	this->Doc.root->AddChild(firstEl);

	this->Doc.root->boxModel.SetPaddingAll(1);
	
	this->Doc.SetAllElementsSizes();
	this->Doc.SetAllElementsPositions();

	this->Doc.root->PrintInfo();
	
}

void Program::ProcessInput(float dt)
{

}
void Program::Update()
{
	// need to make sure projection matrix is updated in code and in shader
	this->projection = glm::ortho(0.0f, static_cast<float>(this->screenWidth), static_cast<float>(this->screenHeight), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("boxshader").Use().SetMatrix4("projection", this->projection);
	//this->Doc.screenWidth = this->screenWidth;
	//this->Doc.screenHeight = this->screenHeight;
	this->Doc.UpdateRootToScreenSize(screenWidth, screenHeight);
	this->Doc.SetAllElementsSizes();
	this->Doc.SetAllElementsPositions();
	
	this->Doc.root->PrintInfo();
}


void Program::Update(float dt)
{
	// need to make sure projection matrix is updated in code and in shader
	this->projection = glm::ortho(0.0f, static_cast<float>(this->screenWidth), static_cast<float>(this->screenHeight), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("boxshader").Use().SetMatrix4("projection", this->projection);
}

void Program::Render()
{
	
	
	//boxRenderer->DrawBox(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
	//boxRenderer->DrawBox(ResourceManager::GetTexture("no_tex"), this->Doc.root->position, this->Doc.root->size, this->Doc.root->rotation, this->Doc.root->idColor);
	//this->Doc.root->RenderBox(boxRenderer);
	this->Doc.RenderDocument(boxRenderer);
}

