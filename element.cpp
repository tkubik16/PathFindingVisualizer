#include <iostream>

#include "element.h"
#include "box_renderer.h"
#include "resource_manager.h"

glm::vec2 rootStart(0.0f, 0.0f);

Element::Element() : alignment(VERTICAL)
{

}

Element::Element(std::string name) : name(name), boxPosition(0, 0), boxSize(0, 0), rotation(0), parent(nullptr), alignment(VERTICAL)
{

}

Element::~Element()
{
	
}

int Element::GetBoxWidth() {
	int boxModelWidth = this->boxModel.width;
	if (this->boxModel.boxWidthMode == PERCENTAGE) {
		return this->parent->GetContentWidth() * (boxModelWidth / 100.0);
	}
	else {
		return boxModelWidth;
	}
}

int Element::GetBoxHeight() {
	int boxModelHeight = this->boxModel.height;
	if (this->boxModel.boxHeightMode == PERCENTAGE) {
		return this->parent->GetContentHeight() * (boxModelHeight / 100.0);
	}
	else {
		return boxModelHeight;
	}
}

int Element::GetContentWidth() {
	return this->contentSize.x;
}

int Element::GetContentHeight() {
	return this->contentSize.y;
}

// Set methods for boxModel Modes
void Element::SetBoxWidthMode(Mode mode) {
	this->boxModel.boxWidthMode = mode;
}
void Element::SetBoxHeightMode(Mode mode) {
	this->boxModel.boxHeightMode = mode;
}
void Element::SetPaddingMode(Mode mode) {
	this->boxModel.padding.mode = mode;
}
void Element::SetMarginMode(Mode mode) {
	this->boxModel.margin.mode = mode;
}
void Element::SetBorderMode(Mode mode) {
	this->boxModel.border.mode = mode;
}

// Get methods for padding to hide the PERCENTAGE vs PIXELS 
int Element::GetPaddingTop() {
	int boxModelTopPadding = this->boxModel.padding.top;
	if (this->boxModel.padding.mode == PERCENTAGE) {
		return this->GetBoxHeight() * (boxModelTopPadding / 100.0);
	}
	return boxModelTopPadding;
}
int Element::GetPaddingBottom() {
	int boxModelBottomPadding = this->boxModel.padding.bottom;
	if (this->boxModel.padding.mode == PERCENTAGE) {
		return this->GetBoxHeight() * (boxModelBottomPadding / 100.0);
	}
	return boxModelBottomPadding;
}
int Element::GetPaddingLeft() {
	int boxModelLeftPadding = this->boxModel.padding.left;
	if (this->boxModel.padding.mode == PERCENTAGE) {
		return this->GetBoxWidth() * (boxModelLeftPadding / 100.0);
	}
	return boxModelLeftPadding;
}
int Element::GetPaddingRight() {
	int boxModelRightPadding = this->boxModel.padding.right;
	if (this->boxModel.padding.mode == PERCENTAGE) {
		return this->GetBoxWidth() * (boxModelRightPadding / 100.0);
	}
	return boxModelRightPadding;
}



void Element::PrintInfo() {
	std::cout << "name:" << std::endl;
	std::cout << this->name << std::endl;

	std::cout << "idColor:" << std::endl;
	std::cout << this->idColor.x << ", " << this->idColor.y << ", " << this->idColor.z << std::endl;

	std::cout << "Alignment: " << std::endl;
	if (this->alignment == VERTICAL)
		std::cout << "VERTICAL" << std::endl;
	else
		std::cout << "HORIZONTAL" << std::endl;

	std::cout << "position (x,y):" << std::endl;
	std::cout << this->boxPosition.x << ", " << this->boxPosition.y << std::endl;

	std::cout << "parent (width, height):" << std::endl;
	std::cout << this->parentWidth << ", " << this->parentHeight << std::endl;

	std::cout << "size (width, height):" << std::endl;
	std::cout << this->boxSize.x << ", " << this->boxSize.y << std::endl;

	std::cout << "ContentPosition: (" << this->contentPosition.x << ", " << this->contentPosition.y << ")" << ", " << "ContentSize: (" << this->contentSize.x << ", " << this->contentSize.y << ")" << std::endl;

	std::cout << "rotation:" << std::endl;
	std::cout << this->rotation << std::endl;

	std::cout << "parent:" << std::endl;
	if (this->parent == nullptr)
		std::cout << " no parent" << std::endl;
	else
		std::cout << " " << this->parent->name << std::endl;

	std::cout << std::endl;
	std::cout << "BoxModel Info:" << std::endl;
	this->boxModel.PrintInfo();
	std::cout << std::endl;
}

void Element::PrintChildren() {
	Element* currChild = this->headChild;
	while (currChild != nullptr) {
		std::cout << currChild->name << std::endl;
		currChild = currChild->childAfter;
	}
}

void Element::CalculatePositions() {
	//std::cout << "Element::CalculateBoxPositions()" << std::endl;
	int xOffset = 0;
	int yOffset = 0;
	if (this->parent == nullptr) {
		//std::cout << this->name << ": Element is root" << std::endl;
		if (this->boxModel.margin.mode == PERCENTAGE) {

		}
		else {
			xOffset = this->boxModel.margin.left;
			yOffset = this->boxModel.margin.top;
		}
		// set box position
		this->boxPosition.x = xOffset;
		this->boxPosition.y = yOffset;
		// set content position
		this->contentPosition.x = xOffset + this->boxModel.padding.left;
		this->contentPosition.y = yOffset + this->boxModel.padding.top;
	}
	else {
		//std::cout << this->name << ": Element has parent" << std::endl;
		// TODO: check if first child or not. will need to calculate based on parent if first child but on previous child if not first child
		int parentContentX = this->parent->contentPosition.x;
		int parentContentY = this->parent->contentPosition.y;

		// set box position
		this->boxPosition.x = parentContentX;
		this->boxPosition.y = parentContentY;
	}
}

bool FirstChildToParent(Element* element) {
	Element* parent = element->parent;
	if (parent->headChild == element) {
		//std::cout << "Element::FirstChildToParent()" << std::endl;
		//std::cout << element->name << std::endl;
		return true;
	}
	return false;
}

void Element::CalculateBoxPosition() {
	//std::cout << "Element::CalculateBoxPosition():" << std::endl;
	if (this->parent == nullptr) {
		//std::cout << "this->parent == nullptr" << std::endl;
		this->CalculateBoxPositionRoot();
		return;
	}
	else if (this->parent->alignment == HORIZONTAL) {
		//std::cout << "alignment == horizontal" << std::endl;
		this->CalculateBoxPositionHorizontal();
	}
	else if (this->parent->alignment == VERTICAL) {
		//std::cout << "alignment == vertical" << std::endl;
		this->CalculateBoxPositionVertical();
	}
}

void Element::CalculateBoxPositionRoot() {
	int xOffset = 0;
	int yOffset = 0;
	// if the element is root
	if (this->parent == nullptr) {
		//std::cout << this->name << ": Element is root" << std::endl;
		if (this->boxModel.margin.mode == PERCENTAGE) {

		}
		else {
			xOffset = this->boxModel.margin.left;
			yOffset = this->boxModel.margin.top;
		}
		// set box position
		this->boxPosition.x = xOffset;
		this->boxPosition.y = yOffset;
	}
}

void Element::CalculateBoxPositionHorizontal() {
	//std::cout << "Element::CalculateBoxPositionHorizontal():" << std::endl;
	int xOffset = 0;
	int yOffset = 0;
	// if the element is not root. thus having a parent

	//std::cout << this->name << ": Element has parent" << std::endl;
		
	// if the element is the first child it lines up with start of content not taking its left margin into account
	if (FirstChildToParent(this)) {
		int parentContentX = this->parent->contentPosition.x;
		int parentContentY = this->parent->contentPosition.y;

		// set box position
		this->boxPosition.x = parentContentX;
		this->boxPosition.y = parentContentY;
	}
	// if the element is not the first child take into account the position of the child before it and use the largest margin between the two
	else {
		if (this->childBefore == nullptr) {
			std::cout << "ELEMENT::ERROR: childBefore is nullptr when it is not the firstChild to parent" << std::endl;
		}
			
		Element* childBefore = this->childBefore;
		if (childBefore != nullptr)
		{
			int margin = (childBefore->boxModel.margin.right > this->boxModel.margin.left) ? childBefore->boxModel.margin.right : this->boxModel.margin.left;
			int posX = childBefore->boxPosition.x + childBefore->boxSize.x + margin;

			this->boxPosition.x = posX;
			this->boxPosition.y = childBefore->boxPosition.y;
		}
	}
	
}

void Element::CalculateBoxPositionVertical() {
	//std::cout << "Element::CalculateBoxPositionVertical():" << std::endl;
	int xOffset = 0;
	int yOffset = 0;
	// if the element is not root. thus having a parent

	//std::cout << this->name << ": Element has parent" << std::endl;

	// if the element is the first child it lines up with start of content not taking its left margin into account
	if (FirstChildToParent(this)) {
		int parentContentX = this->parent->contentPosition.x;
		int parentContentY = this->parent->contentPosition.y;

		// set box position
		this->boxPosition.x = parentContentX;
		this->boxPosition.y = parentContentY;
	}
	// if the element is not the first child take into account the position of the child before it and use the largest margin between the two
	else {
		if (this->childBefore == nullptr) {
			std::cout << "ELEMENT::ERROR: childBefore is nullptr when it is not the firstChild to parent" << std::endl;
		}

		Element* childBefore = this->childBefore;
		if (childBefore != nullptr)
		{
			int margin = (childBefore->boxModel.margin.bottom > this->boxModel.margin.top) ? childBefore->boxModel.margin.bottom : this->boxModel.margin.top;
			int posY = childBefore->boxPosition.y + childBefore->boxSize.y + margin;

			this->boxPosition.y = posY;
			this->boxPosition.x = childBefore->boxPosition.x;
		}
	}

}

void Element::CalculateContentPosition() {
	this->contentPosition.x = this->boxPosition.x + this->GetPaddingLeft();
	this->contentPosition.y = this->boxPosition.y + this->GetPaddingTop();
}

void Element::CalculateContentSize() {
	int width = this->GetBoxWidth();
	int height = this->GetBoxHeight();

	this->contentSize.x = width - this->GetPaddingLeft() - this->GetPaddingRight();
	if (this->contentSize.x < 0)
		this->contentSize.x = 0;

	this->contentSize.y = height - this->GetPaddingTop() - this->GetPaddingBottom();
	if (this->contentSize.y < 0)
		this->contentSize.y = 0;
}

void Element::CalculateBoxSize() {
	int width = this->GetBoxWidth();
	int height = this->GetBoxHeight();

	this->boxSize.x = width;
	this->boxSize.y = height;
	/*
	int width = this->boxModel.width;
	int height = this->boxModel.height;

	this->boxSize.x = width;
	this->boxSize.y = height;
	*/
	//std::cout << "CalculateSize() of " << this->name << std::endl;
	//std::cout << width << " " << height << std::endl;
}

void Element::SetChildrensParentDimensions() {
	int width = this->contentSize.x;
	int height = this->contentSize.y;

	for (std::vector<Element*>::iterator it = this->children.begin(); it != this->children.end(); ++it) {
		(*it)->SetParentDimensions(width, height);
	}
}

void Element::SetParentDimensions(int width, int height) {
	this->parentWidth = width;
	this->parentHeight = height;
}

void Element::SetFillWidth() {
	if (this->parent == nullptr)
		return;

	this->boxModel.width = this->parentWidth;
}

void Element::SetFillHeight() {
	if (this->parent == nullptr)
		return;

	this->boxModel.height = this->parentHeight;
}

void Element::AddChildToVector(Element* child) {
	this->children.push_back(child);
}

void Element::AddChild(Element* child) {
	child->parent = this;
	if (this->headChild == nullptr) {
		this->headChild = child;
		this->tailChild = child;
	}
		
	this->tailChild->childAfter = child;
	child->childBefore = this->tailChild;
	this->tailChild = child;
}

void Element::RenderBox(BoxRenderer* boxRenderer) {
	boxRenderer->DrawBox(ResourceManager::GetTexture("no_tex"), this->boxPosition, this->boxSize, this->rotation, this->idColor);
}

void Element::RenderContentBox(ContentBoxRenderer* contentBoxRenderer) {
	contentBoxRenderer->DrawContentBox(ResourceManager::GetTexture("no_tex"), this->contentPosition, this->contentSize, this->rotation, glm::vec3(1.0f, 1.0f, 1.0f));
}

void Element::RenderContentBox(ContentBoxRenderer* contentBoxRenderer, bool wireframe) {
	contentBoxRenderer->DrawContentBox(ResourceManager::GetTexture("no_tex"), this->contentPosition, wireframe, this->contentSize, this->rotation, this->idColor);
}

