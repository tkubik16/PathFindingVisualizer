#include <cstdlib>
#include <iostream>
#include <sstream>
#include <queue>

#include "document.h"

Document::Document() 
{
	this->root = new Element("root");
}

Document::Document(int width, int height)
{
	this->root = Document::AddElement("root");
	this->root->parentWidth = width;
	this->root->parentHeight = height;
	
}

Document::~Document()
{
	delete this->root;
}

void Document::Init() {
	this->root->boxModel.content.width = this->root->parentWidth;
	this->root->boxModel.content.height = this->root->parentWidth;
	this->root->CalculateSize();
}

Element* Document::AddElement(std::string name) {
	// Generate vec4 colorId that does not already exist
	int n = 100;
	Element *newElement = new Element();
	newElement->name = name;
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

void Document::RenderDocument(BoxRenderer* boxRenderer) {
	
	std::queue<Element*> elQueue;
	elQueue.push(this->root);

	while (!elQueue.empty()) {
		Element* curr = elQueue.front();
		curr->RenderBox(boxRenderer);
		elQueue.pop();
		for (std::vector<Element*>::iterator it = curr->children.begin(); it != curr->children.end(); ++it) {
			elQueue.push(*it);
		}
	}

}

void LevelOrderTraversal(BoxRenderer* boxRenderer, Element* curr) {
	
}