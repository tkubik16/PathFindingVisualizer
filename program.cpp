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
	ResourceManager::LoadShader("boxOverflowHidden.vert", "boxOverflowHidden.frag", nullptr, "boxOverflowHidden");
	ResourceManager::LoadShader("content.vert", "content.frag", nullptr, "contentshader");
	ResourceManager::LoadShader("contentBoxOverflowHidden.vert", "contentBoxOverflowHidden.frag", nullptr, "contentBoxOverflowHidden");
	// configure shaders
	ResourceManager::GetShader("boxshader").Use().SetInteger("image", 0);
	ResourceManager::GetShader("boxshader").SetMatrix4("projection", this->projection);
	ResourceManager::GetShader("boxshader").SetMatrix4("view", this->view);

	ResourceManager::GetShader("boxOverflowHidden").Use().SetInteger("image", 0);
	ResourceManager::GetShader("boxOverflowHidden").SetMatrix4("projection", this->projection);
	ResourceManager::GetShader("boxOverflowHidden").SetMatrix4("view", this->view);

	ResourceManager::GetShader("contentshader").Use().SetInteger("image", 0);
	ResourceManager::GetShader("contentshader").SetMatrix4("projection", this->projection);
	ResourceManager::GetShader("contentshader").SetMatrix4("view", this->view);

	ResourceManager::GetShader("contentBoxOverflowHidden").Use().SetInteger("image", 0);
	ResourceManager::GetShader("contentBoxOverflowHidden").SetMatrix4("projection", this->projection);
	ResourceManager::GetShader("contentBoxOverflowHidden").SetMatrix4("view", this->view);

	/*
	glm::vec2 screenSize(this->screenWidth, this->screenHeight);
	ResourceManager::GetShader("boxshader").Use().SetVector2f("screenSize", screenSize);
	ResourceManager::GetShader("boxOverflowHidden").Use().SetVector2f("screenSize", screenSize);
	ResourceManager::GetShader("contentshader").Use().SetVector2f("screenSize", screenSize);
	*/

	// load textures
	ResourceManager::LoadTexture("textures/block.png", false, "block");
	ResourceManager::LoadTexture("textures/background.jpg", false, "background");
	ResourceManager::LoadTexture("textures/no_tex.png", false, "no_tex");

	// initialize renderers
	this->renderers = new Renderers();
	this->renderers->boxRenderer = new BoxRenderer(ResourceManager::GetShader("boxshader"), ResourceManager::GetShader("boxOverflowHidden"));
	this->renderers->contentBoxRenderer = new ContentBoxRenderer(ResourceManager::GetShader("contentshader"), ResourceManager::GetShader("contentBoxOverflowHidden"));
	this->renderers->textureRenderer = new TextureRenderer(ResourceManager::GetShader("contentshader"));
	this->renderers->SetScreenSize(this->screenWidth, this->screenHeight);

	// Initialize buffers
	boxBuffer = new Framebuffer(this->screenWidth, this->screenHeight);
	boxBuffer->Init();

	// Elements
	Element* firstBox = this->Doc.AddElement("firstBox");
	Element* secondBox = this->Doc.AddElement("secondBox");
	Element* container = this->Doc.AddElement("container");

	firstBox->boxModel.SetSize(500, 100);
	//firstBox->SetBoxWidthMode(PERCENTAGE);
	firstBox->boxModel.SetPaddingAll(25);
	firstBox->boxModel.SetMarginAll(25);

	secondBox->boxModel.SetSize(500, 100);
	//secondBox->SetBoxWidthMode(PERCENTAGE);
	secondBox->boxModel.SetPaddingAll(25);
	secondBox->boxModel.SetMarginAll(25);

	container->boxModel.SetSize(80, 100);
	container->SetBoxWidthMode(PERCENTAGE);
	container->SetBoxHeightMode(PERCENTAGE);
	
	
	// below here create doc tree maybe
	this->Doc.Init();

	this->Doc.root->boxModel.SetPaddingAll(50);

	this->Doc.root->AddChild(firstBox);
	this->Doc.root->AddChild(secondBox);
	this->Doc.root->alignment = HORIZONTAL;
	this->Doc.root->alignContent = END;
	//this->Doc.root->alignItems = END_ITEMS;
	//this->Doc.root->overflow = VISIBLE;
	
	std::cout << this->Doc.screenWidth << " " << this->Doc.screenHeight << std::endl;
	this->Doc.SetAllElementsScreenSizes(this->screenWidth, this->screenHeight);
	this->Doc.SetAllElementsSizes();
	this->Doc.SetAllElementsChildrenWidthAndHeight();
	this->Doc.SetAllElementsPositions();
	this->Doc.SetAllElementsParentsContentBorders();

	this->Doc.root->PrintInfo();
	//firstBox->PrintInfo();
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
	ResourceManager::GetShader("boxOverflowHidden").Use().SetMatrix4("projection", this->projection);
	ResourceManager::GetShader("contentshader").Use().SetMatrix4("projection", this->projection);
	ResourceManager::GetShader("contentBoxOverflowHidden").Use().SetMatrix4("projection", this->projection);

	/*
	glm::vec2 screenSize(width, height);
	ResourceManager::GetShader("boxshader").Use().SetVector2f("screenSize", screenSize);
	ResourceManager::GetShader("boxOverflowHidden").Use().SetVector2f("screenSize", screenSize);
	ResourceManager::GetShader("contentshader").Use().SetVector2f("screenSize", screenSize);
	*/

	this->renderers->SetScreenSize(width, height);

	// update elements based on screen size change
	this->Doc.UpdateRootToScreenSize(screenWidth, screenHeight);
	this->Doc.SetAllElementsScreenSizes(width, height);
	this->Doc.SetAllElementsSizes();
	this->Doc.SetAllElementsChildrenWidthAndHeight();
	this->Doc.SetAllElementsPositions();
	this->Doc.SetAllElementsParentsContentBorders();

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

