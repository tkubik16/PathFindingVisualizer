#include <cstdlib>
#include <iostream>
#include <sstream>
#include <queue>

#include "document.h"

Document::Document() 
{
	this->root = new Element("root");
}

Document::Document(int width, int height) : randomColors(false), screenWidth(width), screenHeight(height)
{
	
	this->root = Document::AddElement("root");
	this->root->parentWidth = width;
	this->root->parentHeight = height;
	this->root->boxModel.SetSize(width, height);

}

Document::~Document()
{
	delete this->root;
}

void Document::Init() {
	this->root->boxModel.width = this->root->parentWidth;
	this->root->boxModel.height = this->root->parentHeight;
	this->root->CalculateBoxSize();
}

Element* Document::AddElement(std::string name) {
	// initialize random seed:
	if (this->randomColors) {
		srand(time(NULL)); // kinda unnecessary but fun
		//std::cout << "randomColors = true" << std::endl;
	}
	//std::cout << "randomColors = false" << std::endl;

	// Generate vec4 colorId that does not already exist
	int n = 100;
	Element *newElement = new Element(name);
	newElement->name = name;
	newElement->idColor.x = (float)(rand() % n) / 100.0f;
	newElement->idColor.y = (float)(rand() % n) / 100.0f;
	newElement->idColor.z = (float)(rand() % n) / 100.0f;

	while (this->ColorIdExists(newElement->idColor)) {
		newElement->idColor.x = (float)(rand() % n) / 100.0f;
		newElement->idColor.y = (float)(rand() % n) / 100.0f;
		newElement->idColor.z = (float)(rand() % n) / 100.0f;
	}
	

	//std::cout << "New Element added. ColorID: [" << newElement->idColor.x << ", " << newElement->idColor.y << ", " << newElement->idColor.z << "]" << std::endl;
	std::ostringstream ss;
	ss << newElement->idColor.x << "," << newElement->idColor.y << "," << newElement->idColor.z;
	std::string s(ss.str());
	this->colorIdMap[s] = newElement;
	//std::cout << "Map size: " << this->colorIdMap.size() << std::endl;
	//std::cout << std::endl;
	//std::cout << s << std::endl;

	
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

void Document::AddFixedElement(Element* element) {
	FixedElement newEl(element, element->zIndex);
	this->fixedElements.push_back(newEl);
	std::cout << this->fixedElements.back().element->name << " Z-Index: " << this->fixedElements.back().zIndex << std::endl;
}

// Might need a version of this that takes a name and a zIndex
void Document::UpdateFixedElementZIndex(Element* element) {
	for (std::vector<FixedElement>::iterator it = this->fixedElements.begin(); it != this->fixedElements.end(); ++it) {
		if (it->element == element) {
			it->zIndex = element->zIndex;
			std::cout << "Document::UpdateFixedElementZIndex" << std::endl;
			std::cout << it->element->name << " " << it->zIndex << std::endl;
			break;
		}
	}
}

void Document::RenderDocument(Renderers* renderers) {
	//std::cout << "RenderDocument: " << std::endl;
	std::queue<Element*> elQueue;
	elQueue.push(this->root);
	while (!elQueue.empty()) {
		Element* curr = elQueue.front();
		//std::cout << curr->name << std::endl;
		curr->RenderBorder(renderers->borderRenderer);
		curr->RenderBox(renderers->boxRenderer);
		//curr->RenderBorder(renderers->borderRenderer);
		curr->RenderContentBox(renderers->contentBoxRenderer, true);
		elQueue.pop();

		Element* currChild = curr->headChild;
		while (currChild != nullptr) {
			elQueue.push(currChild);
			currChild = currChild->childAfter;
		}

	}
}

void Document::RenderDocumentFromVectors(Renderers* renderers) {
	//std::cout << "RenderDocument: " << std::endl;
	std::queue<Element*> elQueue;
	elQueue.push(this->root);
	while (!elQueue.empty()) {
		Element* curr = elQueue.front();
		curr->RenderBox(renderers->boxRenderer);
		curr->RenderContentBox(renderers->contentBoxRenderer);
		elQueue.pop();
		for (std::vector<Element*>::iterator it = curr->children.begin(); it != curr->children.end(); ++it) {
			elQueue.push(*it);
		}
	}
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

void Document::RenderDocument(ContentBoxRenderer* contentBoxRenderer) {

	std::queue<Element*> elQueue;
	elQueue.push(this->root);

	while (!elQueue.empty()) {
		Element* curr = elQueue.front();
		curr->RenderContentBox(contentBoxRenderer);
		elQueue.pop();
		for (std::vector<Element*>::iterator it = curr->children.begin(); it != curr->children.end(); ++it) {
			elQueue.push(*it);
		}
	}

}

void Document::Update() {
	// reset roots dimensions based on screen size
	this->root->boxModel.SetSize(this->screenWidth, this->screenHeight);
}

void Document::UpdateRootToScreenSize(int screenWidth, int screenHeight) {
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	this->root->boxModel.width = this->screenWidth;
	this->root->boxModel.height = this->screenHeight;
}
/*
void Document::SetAllElementsSizes() {
	std::queue<Element*> elQueue;
	elQueue.push(this->root);

	while (!elQueue.empty()) {
		Element* curr = elQueue.front();
		curr->CalculateBoxSize();
		curr->CalculateContentSize();
		elQueue.pop();
		for (std::vector<Element*>::iterator it = curr->children.begin(); it != curr->children.end(); ++it) {
			elQueue.push(*it);
		}
	}
}
*/

void Document::SetAllElementsSizes() {
	std::queue<Element*> elQueue;
	elQueue.push(this->root);

	while (!elQueue.empty()) {
		Element* curr = elQueue.front();
		curr->CalculateBoxSize();
		curr->CalculateBordersSize();
		curr->CalculateContentSize();
		elQueue.pop();
		Element* currChild = curr->headChild;
		while (currChild != nullptr) {
			elQueue.push(currChild);
			currChild = currChild->childAfter;
		}
	}
}

/*
void Document::SetAllElementsPositions() {
	std::queue<Element*> elQueue;
	elQueue.push(this->root);

	while (!elQueue.empty()) {
		Element* curr = elQueue.front();
		//curr->CalculatePositions();
		curr->CalculateBoxPosition();
		curr->CalculateContentPosition();
		elQueue.pop();
		for (std::vector<Element*>::iterator it = curr->children.begin(); it != curr->children.end(); ++it) {
			elQueue.push(*it);
		}
	}
}
*/

// TODO: Fix this so that FIXED and ABSOLUTE elements are ignored in the positioning
void Document::SetAllElementsPositions() {
	//std::cout << "Document::SetAllElementsPositions():" << std::endl;
	std::queue<Element*> elQueue;
	elQueue.push(this->root);

	while (!elQueue.empty()) {
		Element* curr = elQueue.front();
		
		//std::cout << curr->name << std::endl;
		//curr->CalculatePositions();
		curr->CalculateBorderPosition();
		curr->CalculateBoxPositionBasedOnBorderPosition();
		//curr->CalculateBoxPosition();
		curr->CalculateContentPosition();
		elQueue.pop();
		Element* currChild = curr->headChild;
		while (currChild != nullptr) {
			elQueue.push(currChild);
			currChild = currChild->childAfter;
		}
	}
}

void Document::AdjustElementsIfNonStatic() {
	std::queue<Element*> elQueue;
	elQueue.push(this->root);

	while (!elQueue.empty()) {
		Element* curr = elQueue.front();

		if (curr->positioning.positioningType != STATIC_POSITION) {
			curr->AdjustIfNonStatic();
		}
		curr->CalculateBoxPositionBasedOnBorderPosition();
		curr->CalculateContentPosition();
		elQueue.pop();
		Element* currChild = curr->headChild;
		while (currChild != nullptr) {
			elQueue.push(currChild);
			currChild = currChild->childAfter;
		}
	}
}

void Document::SetAllElementsChildrenWidthAndHeight() {
	std::queue<Element*> elQueue;
	elQueue.push(this->root);

	while (!elQueue.empty()) {
		Element* curr = elQueue.front();

		
		curr->CalculateChildrenWidthWithMargins();
		curr->CalculateChildrenHeightWithMargins();
		curr->CalculateChildrenWidth();
		curr->CalculateChildrenHeight();
		elQueue.pop();
		Element* currChild = curr->headChild;
		while (currChild != nullptr) {
			elQueue.push(currChild);
			currChild = currChild->childAfter;
		}
	}
}

void Document::SetAllElementsScreenSizes(int width, int height) {
	std::queue<Element*> elQueue;
	elQueue.push(this->root);

	while (!elQueue.empty()) {
		Element* curr = elQueue.front();
		curr->SetScreenSize(width, height);
		curr->SetContentScale(this->xscale, this->yscale);
		elQueue.pop();
		Element* currChild = curr->headChild;
		while (currChild != nullptr) {
			elQueue.push(currChild);
			currChild = currChild->childAfter;
		}
	}
}

void Document::SetAllElementsParentsContentBorders() {
	std::queue<Element*> elQueue;
	elQueue.push(this->root);

	while (!elQueue.empty()) {
		Element* curr = elQueue.front();
		glm::vec4 borders = curr->CalculateBorders();
		curr->SetChildrensParentContentBorders(borders);
		elQueue.pop();
		Element* currChild = curr->headChild;
		while (currChild != nullptr) {
			elQueue.push(currChild);
			currChild = currChild->childAfter;
		}
	}
}

void Document::SetAllElementsRealContentBorders() {
	std::queue<Element*> elQueue;
	elQueue.push(this->root);

	while (!elQueue.empty()) {
		Element* curr = elQueue.front();
		
		curr->FindRealContentBorders();
		elQueue.pop();
		Element* currChild = curr->headChild;
		while (currChild != nullptr) {
			elQueue.push(currChild);
			currChild = currChild->childAfter;
		}
	}
}

void Document::SetAllElementsCornerCoords() {
	std::queue<Element*> elQueue;
	elQueue.push(this->root);

	while (!elQueue.empty()) {
		Element* curr = elQueue.front();

		curr->CalculateCornerCoords();
		curr->CalculateBorderCornerCoords();
		elQueue.pop();
		Element* currChild = curr->headChild;
		while (currChild != nullptr) {
			elQueue.push(currChild);
			currChild = currChild->childAfter;
		}
	}
}