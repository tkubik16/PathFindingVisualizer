
#include <iostream>

#include "element.h"


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
	std::cout << "idColor:" << std::endl;
	std::cout << this->idColor.x << ", " << this->idColor.y << ", " << this->idColor.z << std::endl;

	std::cout << "position (x,y):" << std::endl;
	std::cout << this->position.x << ", " << this->position.y << std::endl;

	std::cout << "size (height, width):" << std::endl;
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
