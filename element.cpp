#include <iostream>

#include "element.h"
#include "box_renderer.h"
#include "resource_manager.h"

glm::vec2 rootStart(0.0f, 0.0f);

Element::Element()
{

}

Element::Element(std::string name) : name(name), position(0, 0), size(0, 0), rotation(0), parent(nullptr)
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
	std::cout << this->position.x << ", " << this->position.y << std::endl;

	std::cout << "size (width, height):" << std::endl;
	std::cout << this->size.x << ", " << this->size.y << std::endl;

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

void Element::CalculatePosition() {
	int xOffset = 0;
	int yOffset = 0;
	if (this->parent == nullptr) {
		std::cout << "Element is root" << std::endl;
		if (this->boxModel.margin.mode == PERCENTAGE) {

		}
		else {
			xOffset = this->boxModel.margin.left;
			yOffset = this->boxModel.margin.top;
		}
		this->position.x = xOffset;
		this->position.y = yOffset;
	}
	else {
		std::cout << "Element has parent" << std::endl;

	}
}

void Element::CalculateSize() {
	int width = this->boxModel.content.width + this->boxModel.padding.left + this->boxModel.padding.right;
	int height = this->boxModel.content.height + this->boxModel.padding.top + this->boxModel.padding.bottom;

	this->size.x = width;
	this->size.y = height;

	std::cout << width << " " << height << std::endl;
}

void Element::AddChild(Element* child) {
	this->children.push_back(child);
}

void Element::RenderBox(BoxRenderer* boxRenderer) {
	boxRenderer->DrawBox(ResourceManager::GetTexture("no_tex"), this->position, this->size, this->rotation, this->idColor);
}