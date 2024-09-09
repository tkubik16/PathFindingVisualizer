
#include <iostream>

#include "box_model.h"


BoxModel::BoxModel() : content(50, 50, PIXELS), padding(0, 0, 0, 0, PIXELS), border(0, 0, 0, 0, PIXELS), margin(0, 0, 0, 0, PIXELS)
{

}

BoxModel::~BoxModel() {

}

void BoxModel::PrintInfo() {
	std::cout << "content: ";
	this->content.Print();
	std::cout << std::endl;
}