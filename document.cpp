#include <cstdlib>
#include <iostream>
#include <sstream>

#include "document.h"

Document::Document() 
{
	this->root = new Element("root");
}

Document::Document(int width, int height)
{
	this->root = Document::CreateElement("root");
	this->root->boxModel.content.width = width;
	this->root->boxModel.content.height = height;
}

Document::~Document()
{
	delete this->root;
}

Element* Document::CreateElement(std::string name) {
	// Generate vec4 colorId that does not already exist
	int n = 100;
	Element *newElement = new Element();
	newElement->idColor.x = (float)(rand() % n) / 100.0f;
	newElement->idColor.y = (float)(rand() % n) / 100.0f;
	newElement->idColor.z = (float)(rand() % n) / 100.0f;

	while (this->ColorIdExists(newElement->idColor)) {
		newElement->idColor.x = (float)(rand() % n) / 100.0f;
		newElement->idColor.y = (float)(rand() % n) / 100.0f;
		newElement->idColor.z = (float)(rand() % n) / 100.0f;
	}
	

	std::cout << "New Element added. ColorID: [" << newElement->idColor.x << ", " << newElement->idColor.y << ", " << newElement->idColor.z << "]" << std::endl;
	std::ostringstream ss;
	ss << newElement->idColor.x << "," << newElement->idColor.y << "," << newElement->idColor.z;
	std::string s(ss.str());
	this->colorIdMap[s] = newElement;
	std::cout << "Map size: " << this->colorIdMap.size() << std::endl;
	std::cout << std::endl;

	
	return newElement;
}

bool Document::ColorIdExists(glm::vec3 colorId)
{
	std::ostringstream ss;
	ss << colorId.x << "," << colorId.y << "," << colorId.z;
	std::string s(ss.str());

	
	if (this->colorIdMap.count(s) > 0) {
		return true;
	}

	return false;
}