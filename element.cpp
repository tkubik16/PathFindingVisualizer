#include <iostream>

#include "element.h"
#include "box_renderer.h"
#include "resource_manager.h"

glm::vec2 rootStart(0.0f, 0.0f);

Element::Element()
{

}

Element::Element(std::string name) : name(name), boxPosition(0, 0), boxSize(0, 0), rotation(0), parent(nullptr)
{

}

Element::~Element()
{
	
}



void Element::PrintInfo() {
	std::cout << "name:" << std::endl;
	std::cout << this->name << std::endl;

	std::cout << "idColor:" << std::endl;
	std::cout << this->idColor.x << ", " << this->idColor.y << ", " << this->idColor.z << std::endl;

	std::cout << "position (x,y):" << std::endl;
	std::cout << this->boxPosition.x << ", " << this->boxPosition.y << std::endl;

	std::cout << "parent (width, height):" << std::endl;
	std::cout << this->parentWidth << ", " << this->parentHeight << std::endl;

	std::cout << "size (width, height):" << std::endl;
	std::cout << this->boxSize.x << ", " << this->boxSize.y << std::endl;

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

void Element::CalculatePositions() {
	int xOffset = 0;
	int yOffset = 0;
	if (this->parent == nullptr) {
		std::cout << this->name << ": Element is root" << std::endl;
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
		std::cout << this->name << ": Element has parent" << std::endl;
		// TODO: check if first child or not. will need to calculate based on parent if first child but on previous child if not first child
		int parentContentX = this->parent->contentPosition.x;
		int parentContentY = this->parent->contentPosition.y;

		// set box position
		this->boxPosition.x = parentContentX;
		this->boxPosition.y = parentContentY;
	}
}

void Element::CalculateSize() {
	int width = this->boxModel.width;
	int height = this->boxModel.height;

	this->boxSize.x = width;
	this->boxSize.y = height;

	std::cout << "CalculateSize() of " << this->name << std::endl;
	std::cout << width << " " << height << std::endl;
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

void Element::AddChild(Element* child) {
	this->children.push_back(child);
}

void Element::RenderBox(BoxRenderer* boxRenderer) {
	boxRenderer->DrawBox(ResourceManager::GetTexture("no_tex"), this->boxPosition, this->boxSize, this->rotation, this->idColor);
}