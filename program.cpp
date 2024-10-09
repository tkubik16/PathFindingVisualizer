#include <iostream>

#include "program.h"
#include "box_renderer.h"
#include "content_box_renderer.h"
#include "texture_renderer.h"
#include "resource_manager.h"
#include "element.h"
#include "style.h"


BoxRenderer* boxRenderer;
ContentBoxRenderer* contentBoxRenderer;
//TextureRenderer* textureRenderer;

Element* firstBox;
Element* container1;
Element* container2;
Element* container3;
Element* container4;
Element* c1Box1;
Element* c1Box2;
Element* c1Box3;
Element* c1Box4;
Element* c1Box5;
Element* fixedElement;
StyleSheet* styleSheet;

//Framebuffer* boxBuffer;

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
	ResourceManager::LoadShader("border.vert", "border.frag", nullptr, "bordershader");
	ResourceManager::LoadShader("borderOverflowHidden.vert", "borderOverflowHidden.frag", nullptr, "borderOverflowHidden");
	//ResourceManager::LoadShader("borderOverflowHidden.vert", "borderOverflowHidden.frag", nullptr, "borderOverflowHidden");
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

	ResourceManager::GetShader("bordershader").Use().SetInteger("image", 0);
	ResourceManager::GetShader("bordershader").SetMatrix4("projection", this->projection);
	ResourceManager::GetShader("bordershader").SetMatrix4("view", this->view);

	ResourceManager::GetShader("borderOverflowHidden").Use().SetInteger("image", 0);
	ResourceManager::GetShader("borderOverflowHidden").SetMatrix4("projection", this->projection);
	ResourceManager::GetShader("borderOverflowHidden").SetMatrix4("view", this->view);

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
	this->renderers->borderRenderer = new BorderRenderer(ResourceManager::GetShader("bordershader"), ResourceManager::GetShader("borderOverflowHidden"));
	this->renderers->contentBoxRenderer = new ContentBoxRenderer(ResourceManager::GetShader("contentshader"), ResourceManager::GetShader("contentBoxOverflowHidden"));
	this->renderers->textureRenderer = new TextureRenderer(ResourceManager::GetShader("contentshader"));
	this->renderers->SetScreenSize(this->screenWidth, this->screenHeight);

	// Initialize buffers
	this->boxBuffer = new Framebuffer(this->screenWidth, this->screenHeight);
	this->boxBuffer->Init();

	// StyleSheet
	styleSheet = new StyleSheet();
	styleSheet->Init();
	styleSheet->Print("testStyle");

	// Elements
	container1 = this->Doc.AddElement("container1");
	container1->SetBoxWidthMode(PERCENTAGE);
	container1->SetBoxHeightMode(PERCENTAGE);
	container1->boxModel.SetSize(90, 100 / 4 - 1);
	container1->boxModel.SetPaddingAll(30);
	container1->SetRadius(25);
	container1->SetBorderRadius();
	container1->alignment = HORIZONTAL;
	container1->alignContent = SPACE_AROUND;
	container1->alignItems = CENTER_ITEMS;
	container1->overflow = HIDDEN;
	//container1->alignContent = CENTER_CONTENT;

	container2 = this->Doc.AddElement("container2");
	container2->SetBoxWidthMode(PERCENTAGE);
	container2->SetBoxHeightMode(PERCENTAGE);
	container2->boxModel.SetSize(80, 100 / 4 - 1);
	container2->boxModel.SetPaddingAll(30);
	container2->SetRadius(25);
	container2->boxModel.SetBorderAll(10);
	container2->SetBorderRadius();

	container3 = this->Doc.AddElement("container3");
	container3->SetBoxWidthMode(PERCENTAGE);
	container3->SetBoxHeightMode(PERCENTAGE);
	container3->boxModel.SetSize(70, 100 / 4 - 1);
	container3->boxModel.SetPaddingAll(30);
	container3->SetRadius(25);
	container3->SetBorderRadius();

	container4 = this->Doc.AddElement("container4");
	container4->SetBoxWidthMode(PERCENTAGE);
	container4->SetBoxHeightMode(PERCENTAGE);
	container4->boxModel.SetSize(60, 100 / 4 - 1);
	container4->boxModel.SetPaddingAll(30);
	container4->SetRadius(25);
	container4->SetBorderRadius();

	c1Box1 = this->Doc.AddElement("c1Box1");
	c1Box1->boxModel.SetSize(100, 100);
	c1Box1->boxModel.SetPaddingAll(15);
	c1Box1->SetRadius(0);
	c1Box1->SetBorderRadius();
	c1Box1->boxModel.SetMarginAll(30);

	c1Box2 = this->Doc.AddElement("c1Box2");
	c1Box2->boxModel.SetSize(100, 100);
	c1Box2->boxModel.SetPaddingAll(15);
	c1Box2->SetRadius(10);
	c1Box2->SetBorderRadius();
	c1Box2->boxModel.SetMarginAll(30);

	c1Box3 = this->Doc.AddElement("c1Box3");
	c1Box3->boxModel.SetSize(100, 100);
	c1Box3->boxModel.SetPaddingAll(15);
	c1Box3->SetRadius(20);
	c1Box3->boxModel.SetBorderAll(5);
	c1Box3->SetBorderRadius();
	c1Box3->boxModel.SetMarginAll(30);
	c1Box3->SetPositioningType(STATIC_POSITION);
	c1Box3->hideableViaOverflow = false;
	//c1Box3->positioning.right = 25;
	c1Box3->positioning.centerHorizontally = true;
	c1Box3->positioning.centerVertically = true;

	c1Box4 = this->Doc.AddElement("c1Box4");
	c1Box4->boxModel.SetSize(100, 100);
	c1Box4->boxModel.SetPaddingAll(15);
	c1Box4->SetRadius(30);
	c1Box4->SetBorderRadius();
	c1Box4->boxModel.SetMarginAll(30);

	c1Box5 = this->Doc.AddElement("c1Box5");
	c1Box5->boxModel.SetSize(100, 100);
	c1Box5->boxModel.SetPaddingAll(15);
	c1Box5->SetRadius(50);
	c1Box5->SetBorderRadius();
	c1Box5->boxModel.SetMarginAll(30);
	
	
	// below here create doc tree maybe
	this->Doc.Init();
	this->Doc.root->boxModel.SetPaddingAll(50);
	// TODO: test that margin and border don't affect root
	//this->Doc.root->boxModel.SetMarginAll(5);
	this->Doc.root->AddChild(container1);
	this->Doc.root->AddChild(container2);
	this->Doc.root->AddChild(container3);
	this->Doc.root->AddChild(container4);
	this->Doc.root->alignment = VERTICAL;
	this->Doc.root->alignContent = SPACE_AROUND;
	this->Doc.root->alignItems = END_ITEMS;
	this->Doc.root->overflow = HIDDEN;

	container1->AddChild(c1Box1);
	container1->AddChild(c1Box2);
	container1->AddChild(c1Box3);
	container1->AddChild(c1Box4);
	container1->AddChild(c1Box5);

	
	
	
	//std::cout << this->Doc.screenWidth << " " << this->Doc.screenHeight << std::endl;
	this->Doc.SetAllElementsScreenSizes(this->screenWidth, this->screenHeight);
	this->Doc.SetAllElementsSizes();
	this->Doc.SetAllElementsChildrenWidthAndHeight();
	this->Doc.SetAllElementsPositions();
	this->Doc.AdjustElementsIfNonStatic();
	this->Doc.SetAllElementsParentsContentBorders();
	this->Doc.SetAllElementsRealContentBorders();
	this->Doc.SetAllElementsCornerCoords();

	//container->PrintInfo();
	//firstBox->FindRealContentBorders();
	//this->Doc.root->PrintInfo();
	//container->PrintInfo();
	//firstBox->CalculateCornerCoords();
	//container->PrintCornerCoords();
	//firstBox->PrintCornerCoords();
	//container->PrintCornerCoords();
	//this->Doc.root->PrintPositioning();
	//this->Doc.root->PrintChildrenWidthAndHeight();
	//container1->PrintInfo();
	//c1Box3->PrintInfo();
	//this->Doc.root->PrintCornerCoords();
	//this->Doc.root->PrintBorderCornerCoords();

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
	ResourceManager::GetShader("bordershader").Use().SetMatrix4("projection", this->projection);
	ResourceManager::GetShader("borderOverflowHidden").Use().SetMatrix4("projection", this->projection);

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
	this->Doc.AdjustElementsIfNonStatic();
	this->Doc.SetAllElementsParentsContentBorders();
	this->Doc.SetAllElementsRealContentBorders();
	this->Doc.SetAllElementsCornerCoords();

	//firstBox->PrintRealBorders();
	//container->PrintRealBorders();

	// update framebuffers based on screen size change
	this->boxBuffer->UpdateScreenSize(width, height);
}

void Program::Render()
{
	
	
	//boxRenderer->DrawBox(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
	//boxRenderer->DrawBox(ResourceManager::GetTexture("no_tex"), this->Doc.root->position, this->Doc.root->size, this->Doc.root->rotation, this->Doc.root->idColor);
	//this->Doc.root->RenderBox(boxRenderer);
	//this->Doc.RenderDocument(boxRenderer);
	//this->Doc.RenderDocument(contentBoxRenderer);
	//this->Doc.RenderDocumentFromVectors(this->renderers);
	this->boxBuffer->Bind();
	this->Doc.RenderDocument(this->renderers);
	this->boxBuffer->Unbind();
	this->renderers->textureRenderer->Draw(this->boxBuffer->texture, glm::vec2(0.0, 0.0), glm::vec2(this->screenWidth, this->screenHeight));
	//this->Doc.RenderDocument(this->renderers);
}

void Program::SampleBoxBuffer(double x, double y) {
	std::string colorId = this->boxBuffer->Sample(x, y);
	//std::cout << colorId << std::endl;
	Element* clickedElement = this->GetElement(colorId);
	if (clickedElement != nullptr) {
		std::cout << clickedElement->name << std::endl;
		//clickedElement->PrintInfo();
	}
	
}

void Program::SampleBoxBufferRightClick(double x, double y) {
	std::string colorId = this->boxBuffer->Sample(x, y);
	//std::cout << colorId << std::endl;
	Element* clickedElement = this->GetElement(colorId);
	if (clickedElement != nullptr) {
		//std::cout << clickedElement->name << std::endl;
		clickedElement->PrintInfo();
	}

}


Element* Program::GetElement(std::string colorId) {
	if (this->Doc.colorIdMap.count(colorId) != 0) {
		Element* clickedElement = this->Doc.colorIdMap.at(colorId);
		return clickedElement;
	}
	return nullptr;
}

