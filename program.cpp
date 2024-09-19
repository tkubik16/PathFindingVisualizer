#include <iostream>

#include "program.h"
#include "box_renderer.h"
#include "content_box_renderer.h"
#include "texture_renderer.h"
#include "resource_manager.h"
#include "element.h"

BoxRenderer* boxRenderer;
ContentBoxRenderer* contentBoxRenderer;
//TextureRenderer* textureRenderer;

Framebuffer* boxBuffer;

Program::Program(int width, int height) : Doc(width, height), screenWidth(width), screenHeight(height), Keys(), KeysProcessed(), scrollDist(0.0f), renderers()
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
	ResourceManager::LoadShader("content.vert", "content.frag", nullptr, "contentshader");
	// configure shaders
	ResourceManager::GetShader("boxshader").Use().SetInteger("image", 0);
	ResourceManager::GetShader("boxshader").SetMatrix4("projection", this->projection);
	ResourceManager::GetShader("boxshader").SetMatrix4("view", this->view);

	ResourceManager::GetShader("contentshader").Use().SetInteger("image", 0);
	ResourceManager::GetShader("contentshader").SetMatrix4("projection", this->projection);
	ResourceManager::GetShader("contentshader").SetMatrix4("view", this->view);

	// load textures
	ResourceManager::LoadTexture("textures/block.png", false, "block");
	ResourceManager::LoadTexture("textures/background.jpg", false, "background");
	ResourceManager::LoadTexture("textures/no_tex.png", false, "no_tex");

	// initialize renderers
	this->renderers = new Renderers();
	this->renderers->boxRenderer = new BoxRenderer(ResourceManager::GetShader("boxshader"));
	this->renderers->contentBoxRenderer = new ContentBoxRenderer(ResourceManager::GetShader("contentshader"));
	this->renderers->textureRenderer = new TextureRenderer(ResourceManager::GetShader("contentshader"));

	// Initialize buffers
	boxBuffer = new Framebuffer(this->screenWidth, this->screenHeight);
	boxBuffer->Init();

	Element* firstEl = this->Doc.AddElement("firstEl");
	firstEl->parent = this->Doc.root;

	Element* secondEl = this->Doc.AddElement("secondEl");
	secondEl->parent = this->Doc.root;

	// below here create doc tree maybe
	this->Doc.Init();
	//this->Doc.root->PrintInfo();
	

	firstEl->boxModel.SetSize(100, 100);
	firstEl->boxModel.SetPaddingAll(10);

	secondEl->boxModel.SetSize(50, 50);
	secondEl->boxModel.SetPaddingAll(10);
	//this->Doc.root->CalculatePositions();
	//this->Doc.root->CalculateSize();

	//firstEl->CalculateSize();
	//firstEl->CalculatePositions();
	

	this->Doc.root->AddChild(firstEl);
	this->Doc.root->AddChild(secondEl);

	//this->Doc.root->AddChildToVector(firstEl);
	//this->Doc.root->AddChildToVector(secondEl);

	this->Doc.root->boxModel.SetPaddingAll(50);
	
	this->Doc.SetAllElementsSizes();
	this->Doc.SetAllElementsPositions();

	//this->Doc.root->PrintInfo();
	this->Doc.root->PrintChildren();
	
}

void Program::ProcessInput(float dt)
{

}

void Program::Update()
{
	
}


void Program::Update(float dt)
{
	
}

void Program::UpdateScreenSize(int width, int height) {
	this->screenWidth = width;
	this->screenHeight = height;

	// need to make sure projection matrix is updated in code and in shader
	this->projection = glm::ortho(0.0f, static_cast<float>(this->screenWidth), static_cast<float>(this->screenHeight), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("boxshader").Use().SetMatrix4("projection", this->projection);
	ResourceManager::GetShader("contentshader").Use().SetMatrix4("projection", this->projection);

	// update elements based on screen size change
	this->Doc.UpdateRootToScreenSize(screenWidth, screenHeight);
	this->Doc.SetAllElementsSizes();
	this->Doc.SetAllElementsPositions();

	// update framebuffers based on screen size change
	boxBuffer->UpdateScreenSize(width, height);
}

void Program::Render()
{
	
	
	//boxRenderer->DrawBox(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
	//boxRenderer->DrawBox(ResourceManager::GetTexture("no_tex"), this->Doc.root->position, this->Doc.root->size, this->Doc.root->rotation, this->Doc.root->idColor);
	//this->Doc.root->RenderBox(boxRenderer);
	//this->Doc.RenderDocument(boxRenderer);
	//this->Doc.RenderDocument(contentBoxRenderer);
	//this->Doc.RenderDocumentFromVectors(this->renderers);
	boxBuffer->Bind();
	this->Doc.RenderDocument(this->renderers);
	boxBuffer->Unbind();
	this->renderers->textureRenderer->Draw(boxBuffer->texture, glm::vec2(0.0, 0.0), glm::vec2(this->screenWidth, this->screenHeight));
	//this->Doc.RenderDocument(this->renderers);
}

