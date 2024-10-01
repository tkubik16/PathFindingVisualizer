#include <iostream>

#include "element.h"
#include "box_renderer.h"
#include "resource_manager.h"

glm::vec2 rootStart(0.0f, 0.0f);

Element::Element() : alignment(VERTICAL)
{

}

Element::Element(std::string name) : 
	name(name), 
	zIndex(1),
	boxPosition(0, 0), 
	boxSize(0, 0), 
	rotation(0), 
	parent(nullptr), 
	alignment(VERTICAL), 
	overflow(HIDDEN), 
	alignContent(START), 
	alignItems(START_ITEMS),
	childAfter(nullptr), 
	childBefore(nullptr), 
	parentContentBorders(glm::vec4(1, -1, -1, 1)), 
	theRealContentBorders(glm::vec4(1, -1, -1, 1)), 
	radius(0)

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
// These use the percentage of the elements box not the parent or screen
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

// Get methods for margin to hide the PERCENTAGE vs PIXELS 
// These use the percentage of the elements box not the parent or screen
// TODO: within the percentage if statement add two branches for percentage of self or parent (margin only thing, doesn't make tons of sense for padding)
int Element::GetMarginTop() {
	int boxModelTopMargin = this->boxModel.margin.top;
	if (this->boxModel.margin.mode == PERCENTAGE) {
		return this->GetBoxHeight() * (boxModelTopMargin / 100.0);
	}
	return boxModelTopMargin;
}
int Element::GetMarginBottom() {
	int boxModelMarginPadding = this->boxModel.margin.bottom;
	if (this->boxModel.margin.mode == PERCENTAGE) {
		return this->GetBoxHeight() * (boxModelMarginPadding / 100.0);
	}
	return boxModelMarginPadding;
}
int Element::GetMarginLeft() {
	int boxModelLeftMargin = this->boxModel.margin.left;
	if (this->boxModel.margin.mode == PERCENTAGE) {
		return this->GetBoxWidth() * (boxModelLeftMargin / 100.0);
	}
	return boxModelLeftMargin;
}
int Element::GetMarginRight() {
	int boxModelRightMargin = this->boxModel.margin.right;
	if (this->boxModel.margin.mode == PERCENTAGE) {
		return this->GetBoxWidth() * (boxModelRightMargin / 100.0);
	}
	return boxModelRightMargin;
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

	std::cout << "radius:" << std::endl;
	std::cout << this->radius << std::endl;

	std::cout << "parent:" << std::endl;
	if (this->parent == nullptr)
		std::cout << " no parent" << std::endl;
	else
		std::cout << " " << this->parent->name << std::endl;

	std::cout << "childBefore:" << std::endl;
	if (this->childBefore == nullptr)
		std::cout << " no childBefore" << std::endl;
	else
		std::cout << " " << this->childBefore->name << std::endl;

	std::cout << "childAfter:" << std::endl;
	if (this->childAfter == nullptr)
		std::cout << " no childAfter" << std::endl;
	else
		std::cout << " " << this->childAfter->name << std::endl;


	std::cout << "childrenWidth: " << this->childrenWidth << " childrenHeight: " << this->childrenHeight << std::endl;
	std::cout << "AlignContent: ";
	if (this->alignContent == CENTER_CONTENT)
		std::cout << "CENTER";
	else if (this->alignContent == START)
		std::cout << "START";
	else if (this->alignContent == END)
		std::cout << "END";
	std::cout << std::endl;

	std::cout << std::endl;
	std::cout << "BoxModel Info:" << std::endl;
	this->boxModel.PrintInfo();
	std::cout << std::endl;
}

void Element::PrintPositioning() {
	std::cout << "PositionType: " << std::endl;
	if (this->positioning.positioningType == STATIC) {
		std::cout << "STATIC" << std::endl;
	}
	else if (this->positioning.positioningType == RELATIVE) {
		std::cout << "RELATIVE" << std::endl;
	}
	else if (this->positioning.positioningType == ABSOLUTE) {
		std::cout << "ABSOLUTE" << std::endl;
	}
	else if (this->positioning.positioningType == FIXED) {
		std::cout << "FIXED" << std::endl;
	}
}

void Element::PrintBorders() {
	std::cout << "Borders(topY, bottomY, leftX, rightX):" << std::endl;
	std::cout << this->parentContentBorders.x << " " << this->parentContentBorders.y << " " << this->parentContentBorders.z << " " << this->parentContentBorders.w << std::endl;
}

void Element::PrintRealBorders() {
	std::cout << "theRealBorders(topY, bottomY, leftX, rightX):" << std::endl;
	std::cout << this->theRealContentBorders.x << " " << this->theRealContentBorders.y << " " << this->theRealContentBorders.z << " " << this->theRealContentBorders.w << std::endl;
}

void Element::PrintCornerCoords() {
	std::cout << "position (x,y):" << std::endl;
	std::cout << this->boxPosition.x << ", " << this->boxPosition.y << std::endl;

	std::cout << "size (width, height):" << std::endl;
	std::cout << this->boxSize.x << ", " << this->boxSize.y << std::endl;

	std::cout << "topLeft (x,y):" << std::endl;
	std::cout << "(" << this->topLeft.x << ", " << this->topLeft.y << ")" << std::endl;

	std::cout << "topRight (x,y):" << std::endl;
	std::cout << "(" << this->topRight.x << ", " << this->topRight.y << ")" << std::endl;

	std::cout << "bottomLeft (x,y):" << std::endl;
	std::cout << "(" << this->bottomLeft.x << ", " << this->bottomLeft.y << ")" << std::endl;

	std::cout << "bottomRight (x,y):" << std::endl;
	std::cout << "(" << this->bottomRight.x << ", " << this->bottomRight.y << ")" << std::endl;
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

bool FirstInlineChildToParent(Element* element) {
	Element* parent = element->parent;
	if (parent->headChild == nullptr) return false;

	Element* curr = parent->headChild;
	while (curr != nullptr) {

		if (curr->positioning.positioningType == STATIC || curr->positioning.positioningType == RELATIVE) {
			if (curr == element) return true;
			else break;
		}
		curr = curr->childAfter;
	}
	return false;
}

Element* GetInlineChildBefore(Element* element) {
	if (element->childBefore == nullptr) {
		std::cout << "ERROR::ELEMENT GetInlineChildBefore(): element does not have a child before." << std::endl;
		return nullptr;
	}
	Element* curr = element->childBefore;
	while (curr->positioning.positioningType == FIXED || curr->positioning.positioningType == ABSOLUTE) {
		if (curr->childBefore == nullptr) {
			std::cout << "ERROR::ELEMENT GetInlineChildBefore(): Somehow no element before this one is STATIC or RELATIVE." << std::endl;
			return nullptr;
		}
		curr = curr->childBefore;
	}
	return curr;
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
	if (this->positioning.positioningType == ABSOLUTE || this->positioning.positioningType == FIXED) {
		return;
	}
	//std::cout << "Element::CalculateBoxPositionHorizontal():" << std::endl;
	int xOffset = 0;
	int yOffset = 0;
	// if the element is not root. thus having a parent

	//std::cout << this->name << ": Element has parent" << std::endl;
	int maxHeight = this->parent->childrenHeight;
	int parentContentX = this->parent->contentPosition.x;
	int parentContentY = this->parent->contentPosition.y;
	// if the element is the first child it lines up with start of content not taking its left margin into account
	if (FirstInlineChildToParent(this)) {
		

		// set box position x value
		if (this->parent->alignContent == START) {
			this->boxPosition.x = parentContentX;
			//this->boxPosition.y = parentContentY;
		}
		else if (this->parent->alignContent == CENTER_CONTENT) {
			int childrenWidth = this->parent->childrenWidth;
			int parentWidth = this->parent->GetContentWidth();

			int childrenCenter = childrenWidth / 2;
			int parentCenter = parentWidth / 2;

			int childrenStartX = parentContentX + parentCenter - childrenCenter;

			this->boxPosition.x = childrenStartX;
			//this->boxPosition.y = parentContentY;

		}
		else if (this->parent->alignContent == END) {
			int childrenWidth = this->parent->childrenWidth;
			int parentWidth = this->parent->GetContentWidth();


			int childrenStartX = parentContentX + parentWidth - childrenWidth;

			this->boxPosition.x = childrenStartX;
			//this->boxPosition.y = parentContentY;

		}
		else if (this->parent->alignContent == SPACE_EVENLY) {

		}
		else if (this->parent->alignContent == SPACE_BETWEEN) {

		}
		else if (this->parent->alignContent == SPACE_AROUND) {

		}
		else {
			this->boxPosition.x = parentContentX;
			//this->boxPosition.y = parentContentY;
		}

		// set box position y value
		if (this->parent->alignItems == START_ITEMS) {
			this->boxPosition.y = parentContentY;
		}
		else if (this->parent->alignItems == CENTER_ITEMS) {

			int yOffset = (maxHeight - this->boxSize.y) / 2;
			this->boxPosition.y = parentContentY + yOffset;

		}
		else if (this->parent->alignItems == END_ITEMS) {
			int yOffset = maxHeight - this->boxSize.y;
			this->boxPosition.y = parentContentY + yOffset;

		}
		else {
			this->boxPosition.y = parentContentY;
		}
		
		
	}
	// if the element is not the first child take into account the position of the child before it and use the largest margin between the two
	else {
		if (this->childBefore == nullptr) {
			std::cout << "ELEMENT::ERROR: childBefore is nullptr when it is not the firstChild to parent" << std::endl;
		}
			
		//Element* childBefore = this->childBefore;
		Element* childBefore = GetInlineChildBefore(this);
		if (childBefore != nullptr)
		{
			int margin = (childBefore->GetMarginRight() > this->GetMarginLeft()) ? childBefore->GetMarginRight() : this->GetMarginLeft();
			int posX = childBefore->boxPosition.x + childBefore->boxSize.x + margin;

			this->boxPosition.x = posX;
			if (this->parent->alignItems == START_ITEMS) {
				this->boxPosition.y = childBefore->boxPosition.y;
			}
			else if (this->parent->alignItems == CENTER_ITEMS) {
				int yOffset = (maxHeight - this->boxSize.y) / 2;
				this->boxPosition.y = parentContentY + yOffset;
			}
			else if (this->parent->alignItems == END_ITEMS) {
				int yOffset = maxHeight - this->boxSize.y;
				this->boxPosition.y = parentContentY + yOffset;
			}
			else {
				this->boxPosition.y = parentContentY;
			}
			
		}
	}
	
}

void Element::CalculateBoxPositionVertical() {
	if (this->positioning.positioningType == ABSOLUTE || this->positioning.positioningType == FIXED) {
		return;
	}

	//std::cout << "Element::CalculateBoxPositionVertical():" << std::endl;
	int xOffset = 0;
	int yOffset = 0;
	// if the element is not root. thus having a parent

	//std::cout << this->name << ": Element has parent" << std::endl;
	int maxWidth = this->parent->childrenWidth;
	int parentContentX = this->parent->contentPosition.x;
	int parentContentY = this->parent->contentPosition.y;
	// if the element is the first child it lines up with start of content not taking its left margin into account
	if (FirstInlineChildToParent(this)) {
		

		// set box position for y 
		if (this->parent->alignContent == START) {
			//this->boxPosition.x = parentContentX;
			this->boxPosition.y = parentContentY;
		}
		else if (this->parent->alignContent == CENTER_CONTENT) {
			int childrenHeight = this->parent->childrenHeight;
			int parentHeight = this->parent->GetContentHeight();

			int childrenCenter = childrenHeight / 2;
			int parentCenter = parentHeight / 2;

			int childrenStartY = parentContentY + parentCenter - childrenCenter;

			//this->boxPosition.x = parentContentX;
			this->boxPosition.y = childrenStartY;

		}
		else if (this->parent->alignContent == END) {
			int childrenHeight = this->parent->childrenHeight;
			int parentHeight = this->parent->GetContentHeight();


			int childrenStartY = parentContentY + parentHeight - childrenHeight;

			//this->boxPosition.x = parentContentX;
			this->boxPosition.y = childrenStartY;

		}
		else if (this->parent->alignContent == SPACE_EVENLY) {

		}
		else if (this->parent->alignContent == SPACE_BETWEEN) {

		}
		else if (this->parent->alignContent == SPACE_AROUND) {

		}
		else {
			//this->boxPosition.x = parentContentX;
			this->boxPosition.y = parentContentY;
		}

		// set box position for x 
		if (this->parent->alignItems == START_ITEMS) {
			this->boxPosition.x = parentContentX;
		}
		else if (this->parent->alignItems == CENTER_ITEMS) {

			int xOffset = (maxWidth - this->boxSize.x) / 2;
			this->boxPosition.x = parentContentX + xOffset;

		}
		else if (this->parent->alignItems == END_ITEMS) {
			int xOffset = maxWidth - this->boxSize.x;
			this->boxPosition.x = parentContentX + xOffset;

		}
		else {
			this->boxPosition.x = parentContentX;
		}


	}
	// if the element is not the first child take into account the position of the child before it and use the largest margin between the two
	else {
		if (this->childBefore == nullptr) {
			std::cout << "ELEMENT::ERROR: childBefore is nullptr when it is not the firstChild to parent" << std::endl;
		}

		Element* childBefore = GetInlineChildBefore(this);

		//Element* childBefore = this->childBefore;
		if (childBefore != nullptr)
		{
			int margin = (childBefore->GetMarginBottom() > this->GetMarginTop()) ? childBefore->GetMarginBottom() : this->GetMarginTop();
			int posY = childBefore->boxPosition.y + childBefore->boxSize.y + margin;

			this->boxPosition.y = posY;
			if (this->parent->alignItems == START_ITEMS) {
				this->boxPosition.x = parentContentX;
			}
			else if (this->parent->alignItems == CENTER_ITEMS) {
				int xOffset = (maxWidth - this->boxSize.x) / 2;
				this->boxPosition.x = parentContentX + xOffset;
			}
			else if (this->parent->alignItems == END_ITEMS) {
				int xOffset = maxWidth - this->boxSize.x;
				this->boxPosition.x = parentContentX + xOffset;
			}
			else {
				this->boxPosition.x = parentContentX;
			}
		}
	}

}
// TODO: make the adjustments for RELATIVE, FIXED, ABSOLUTE
void Element::AdjustIfNonStatic() {
	if (this->positioning.positioningType == FIXED) {
		this->CalculatePositionFixed();
	}
}

/*
~fixed

A fixed position element is positioned relative to the viewport, or the browser window
itself. The viewport doesn’t change when the window is scrolled, so a fixed positioned
element will stay right where it is when the page is scrolled.

This might be used for something like a navigation bar that you want to remain visible at
all times regardless of the pages scroll position. The concern with fixed positioning is
that it can cause situations where the fixed element overlaps content such that is is
inaccessible. The trick is having enough space to avoid that, and tricks like this.
*/
void Element::CalculatePositionFixed() {
	if (this->positioning.positionCenterHorizontally == true) {

	}
	else if (this->positioning.positionCenterVertically == true) {

	}
}

int Element::GetTop() {
	if (this->positioning.mode == PIXELS) return this->positioning.top;

	int screenHeight = this->screenHeight;

	float percentage = (float)this->positioning.top / 100.0;
	return screenHeight * percentage;
}

int Element::GetBottom() {
	if (this->positioning.mode == PIXELS) return this->positioning.bottom;

	int screenHeight = this->screenHeight;

	float percentage = (float)this->positioning.bottom / 100.0;
	return screenHeight * percentage;
}

int Element::GetLeft() {
	if (this->positioning.mode == PIXELS) return this->positioning.left;

	int screenWidth = this->screenWidth;

	float percentage = (float)this->positioning.left / 100.0;
	return screenWidth * percentage;
}

int Element::GetRight() {
	if (this->positioning.mode == PIXELS) return this->positioning.right;

	int screenWidth = this->screenWidth;

	float percentage = (float)this->positioning.right / 100.0;
	return screenWidth * percentage;
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
	else {
		this->tailChild->childAfter = child;
		child->childBefore = this->tailChild;
		this->tailChild = child;
	}
	
}

void Element::RenderBox(BoxRenderer* boxRenderer) {
	if (this->parent == nullptr) {
		boxRenderer->DrawBox(ResourceManager::GetTexture("no_tex"), this->boxPosition, this->boxSize, this->topLeft, this->topRight, this->bottomLeft, this->bottomRight, this->GetRadius(), glm::vec2(this->screenWidth, this->screenHeight), this->rotation, this->idColor);
	}
	else if (this->parent->overflow == HIDDEN) {
		//std::cout << "HIDDEN" << std::endl;
		//boxRenderer->DrawBox(ResourceManager::GetTexture("no_tex"), this->boxPosition, this->boxSize, this->rotation, this->idColor);
		boxRenderer->DrawBoxOverflowHidden(ResourceManager::GetTexture("no_tex"), this->boxPosition, this->boxSize, this->parent->contentPosition, this->parent->contentSize, this->theRealContentBorders, this->topLeft, this->topRight, this->bottomLeft, this->bottomRight, this->GetRadius(), glm::vec2(this->screenWidth, this->screenHeight), this->rotation, this->idColor);
	}
	else {
		//std::cout << "VISIBLE" << std::endl;
		boxRenderer->DrawBox(ResourceManager::GetTexture("no_tex"), this->boxPosition, this->boxSize, this->topLeft, this->topRight, this->bottomLeft, this->bottomRight, this->GetRadius(), glm::vec2(this->screenWidth, this->screenHeight), this->rotation, this->idColor);
	}
	
}

void Element::RenderContentBox(ContentBoxRenderer* contentBoxRenderer) {
	if (this->parent == nullptr) {
		contentBoxRenderer->DrawContentBox(ResourceManager::GetTexture("no_tex"), this->contentPosition, this->contentSize, this->rotation, this->idColor);
	}
	else if (this->parent->overflow == HIDDEN) {
		//std::cout << "HIDDEN" << std::endl;
		//boxRenderer->DrawBox(ResourceManager::GetTexture("no_tex"), this->boxPosition, this->boxSize, this->rotation, this->idColor);
		contentBoxRenderer->DrawContentBoxOverflowHidden(ResourceManager::GetTexture("no_tex"), this->contentPosition, this->contentSize, this->parent->contentPosition, this->parent->contentSize, this->rotation, this->idColor);
	}
	else {
		//std::cout << "VISIBLE" << std::endl;
		contentBoxRenderer->DrawContentBox(ResourceManager::GetTexture("no_tex"), this->contentPosition, this->contentSize, this->rotation, this->idColor);
	}
}

void Element::RenderContentBox(ContentBoxRenderer* contentBoxRenderer, bool wireframe) {
	if (this->parent == nullptr) {
		contentBoxRenderer->DrawContentBox(ResourceManager::GetTexture("no_tex"), this->contentPosition, wireframe, this->contentSize, this->rotation, this->idColor);
	}
	else if (this->parent->overflow == HIDDEN) {
		//std::cout << "HIDDEN" << std::endl;
		//contentBoxRenderer->DrawContentBox(ResourceManager::GetTexture("no_tex"), this->contentPosition, wireframe, this->contentSize, this->rotation, this->idColor);
		contentBoxRenderer->DrawContentBoxOverflowHidden(ResourceManager::GetTexture("no_tex"), this->contentPosition, this->contentSize, this->parent->contentPosition, this->parent->contentSize, this->theRealContentBorders, wireframe, this->rotation, this->idColor);
	}
	else {
		//std::cout << "VISIBLE" << std::endl;
		contentBoxRenderer->DrawContentBox(ResourceManager::GetTexture("no_tex"), this->contentPosition, wireframe, this->contentSize, this->rotation, this->idColor);
	}
}

void Element::CalculateChildrenWidthWithMargins() {
	if (this->headChild == nullptr) {
		this->childrenWidth = 0;
	}
	int width = 0;
	if (this->alignment == HORIZONTAL) {
		Element* curr = this->headChild;
		while (curr != nullptr) {
			if (curr->positioning.positioningType == FIXED || curr->positioning.positioningType == ABSOLUTE) { // these are not taken into account for the width and height
				curr = curr->childAfter;
				continue; 
			}
			width += curr->boxSize.x;
			if (curr->childAfter != nullptr) {
				// get both margins
				int currMargin = curr->childAfter->GetMarginRight();
				int nextMargin = curr->GetMarginLeft();
				width += (currMargin > nextMargin) ? currMargin : nextMargin;
			}
			curr = curr->childAfter;
		}
	}
	else if (this->alignment == VERTICAL) {
		Element* curr = this->headChild;
		while (curr != nullptr) {
			if (curr->positioning.positioningType == FIXED || curr->positioning.positioningType == ABSOLUTE) { // these are not taken into account for the width and height
				curr = curr->childAfter;
				continue;
			}			
			if (curr->boxSize.x > width) {
				width = curr->boxSize.x;
			}
			curr = curr->childAfter;
		}
	}
	this->childrenWidthWithMargins = width;
}

void Element::CalculateChildrenHeightWithMargins() {
	if (this->headChild == nullptr) {
		this->childrenHeight = 0;
	}
	int height = 0;
	if (this->alignment == HORIZONTAL) {
		Element* curr = this->headChild;
		while (curr != nullptr) {
			if (curr->positioning.positioningType == FIXED || curr->positioning.positioningType == ABSOLUTE) { // these are not taken into account for the width and height
				curr = curr->childAfter;
				continue;
			}
			if (curr->boxSize.y > height) {
				height = curr->boxSize.y;
			}
			curr = curr->childAfter;
		}
	}
	else if (this->alignment == VERTICAL) {
		Element* curr = this->headChild;
		while (curr != nullptr) {
			if (curr->positioning.positioningType == FIXED || curr->positioning.positioningType == ABSOLUTE) { // these are not taken into account for the width and height
				curr = curr->childAfter;
				continue;
			}
			height += curr->boxSize.y;
			curr = curr->childAfter;
		}
	}
	this->childrenHeightWithMargins = height;
}

void Element::CalculateChildrenWidth() {
	if (this->headChild == nullptr) {
		this->childrenWidth = 0;
	}
	int width = 0;
	if (this->alignment == HORIZONTAL) {
		Element* curr = this->headChild;
		while (curr != nullptr) {
			if (curr->positioning.positioningType == FIXED || curr->positioning.positioningType == ABSOLUTE) { // these are not taken into account for the width and height
				curr = curr->childAfter;
				continue;
			}
			width += curr->boxSize.x;
			curr = curr->childAfter;
		}
	}
	else if (this->alignment == VERTICAL) {
		Element* curr = this->headChild;
		while (curr != nullptr) {
			if (curr->positioning.positioningType == FIXED || curr->positioning.positioningType == ABSOLUTE) { // these are not taken into account for the width and height
				curr = curr->childAfter;
				continue;
			}
			if (curr->boxSize.x > width) {
				width = curr->boxSize.x;
			}
			curr = curr->childAfter;
		}
	}
	this->childrenWidth = width;
}

void Element::CalculateChildrenHeight() {
	if (this->headChild == nullptr) {
		this->childrenHeight = 0;
	}
	int height = 0;
	if (this->alignment == HORIZONTAL) {
		Element* curr = this->headChild;
		while (curr != nullptr) {
			if (curr->boxSize.y > height) {
				height = curr->boxSize.y;
			}
			curr = curr->childAfter;
		}
	}
	else if (this->alignment == VERTICAL) {
		Element* curr = this->headChild;
		while (curr != nullptr) {
			height += curr->boxSize.y;
			if (curr->childAfter != nullptr) {
				// get both margins
				int currMargin = curr->childAfter->GetMarginBottom();
				int nextMargin = curr->GetMarginTop();
				height += (currMargin > nextMargin) ? currMargin : nextMargin;
			}
			curr = curr->childAfter;
		}
	}
	this->childrenHeight = height;
}

glm::vec4 Element::CalculateBorders() {

	glm::vec2 screenSize(this->screenWidth, this->screenHeight);
	float topY = (((screenSize.y - this->contentPosition.y) / screenSize.y) * 2.0) - 1.0;
	float bottomY = (((screenSize.y - (this->contentPosition.y + this->contentSize.y)) / screenSize.y) * 2.0) - 1.0;
	float leftX = ((this->contentPosition.x / screenSize.x) * 2.0) - 1.0;
	float rightX = (((this->contentPosition.x + this->contentSize.x) / screenSize.x) * 2.0) - 1.0;

	return glm::vec4(topY, bottomY, leftX, rightX);
}

void Element::SetChildrensParentContentBorders(glm::vec4 borders) {
	if (this->headChild != nullptr) {
		Element* curr = this->headChild;
		while (curr != nullptr) {
			curr->parentContentBorders = borders;
			//curr->theRealContentBorders = borders;
			curr = curr->childAfter;
		}
	}
}

void Element::SetScreenSize(int width, int height) {
	this->screenWidth = width;
	this->screenHeight = height;
}

void Element::FindRealContentBorders() {
	Element* curr = this;
	this->theRealContentBorders = this->parentContentBorders;
	//borders(topY, bottomY, leftX, rightX);
	while (curr != nullptr) {
		if (curr->parentContentBorders.x < this->theRealContentBorders.x) {
			this->theRealContentBorders.x = curr->parentContentBorders.x;
		}
		if (curr->parentContentBorders.y > this->theRealContentBorders.y) {
			this->theRealContentBorders.y = curr->parentContentBorders.y;
		}
		if (curr->parentContentBorders.z > this->theRealContentBorders.z) {
			this->theRealContentBorders.z = curr->parentContentBorders.z;
		}
		if (curr->parentContentBorders.w < this->theRealContentBorders.w) {
			this->theRealContentBorders.w = curr->parentContentBorders.w;
		}
		
		//std::cout << curr->name << std::endl;
		//curr->PrintRealBorders();
		curr = curr->parent;
	}
	//std::cout << std::endl;
}

void Element::SetRadius(int radius) {
	this->radius = radius;
}

void Element::CalculateCornerCoords() {
	int width = this->boxSize.x;
	int height = this->boxSize.y;
	
	int smallSide = (width < height) ? width : height;

	int maxRadius = this->radius;
	if (this->radius > smallSide / 2) {
		maxRadius = smallSide / 2;
	}
	// set top left coord currently not screen coords
	this->topLeft.x = this->boxPosition.x + maxRadius;
	this->topLeft.y = this->boxPosition.y + maxRadius;

	// set top right
	this->topRight.x = this->boxPosition.x + width - maxRadius;
	this->topRight.y = this->boxPosition.y + maxRadius;

	// set bottomLeft
	this->bottomLeft.x = this->boxPosition.x + maxRadius;
	this->bottomLeft.y = this->boxPosition.y + height - maxRadius;

	// set bottomRight
	this->bottomRight.x = this->boxPosition.x + width - maxRadius;
	this->bottomRight.y = this->boxPosition.y + height - maxRadius;

	// convert to screen coords
	this->topLeft.x = (this->topLeft.x / this->screenWidth) * 2 - 1;
	this->topLeft.y = ((this->screenHeight - this->topLeft.y ) / this->screenHeight) * 2 - 1;

	// TODO: Fix these screen coord calculations
	this->topRight.x = (this->topRight.x / this->screenWidth) * 2 - 1;
	this->topRight.y = ((this->screenHeight - this->topRight.y) / this->screenHeight) * 2 - 1;

	this->bottomLeft.x = (this->bottomLeft.x / this->screenWidth) * 2 - 1;
	this->bottomLeft.y = ((this->screenHeight - this->bottomLeft.y) / this->screenHeight) * 2 - 1;

	this->bottomRight.x = (this->bottomRight.x / this->screenWidth) * 2 - 1;
	this->bottomRight.y = ((this->screenHeight - this->bottomRight.y) / this->screenHeight) * 2 - 1;

}

float Element::GetRadius() {
	int width = this->boxSize.x;
	int height = this->boxSize.y;

	int smallSide = (width < height) ? width : height;

	int maxRadius = this->radius;
	if (this->radius > smallSide / 2) {
		maxRadius = smallSide / 2;
	}
	//std::cout << maxRadius << std::endl;
	//return (float)((maxRadius / this->screenWidth) * 2 - 1);
	return (float)maxRadius;
}