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
	borderPosition(0, 0),
	borderSize(0, 0),
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
	radius(0),
	borderRadius(0),
	hideableViaOverflow(true)

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
		//return boxModelWidth;
		if (this->name == "root") {
			return boxModelWidth;
		}
		return boxModelWidth * this->xscale;
	}
}

int Element::GetBoxHeight() {
	int boxModelHeight = this->boxModel.height;
	if (this->boxModel.boxHeightMode == PERCENTAGE) {
		return this->parent->GetContentHeight() * (boxModelHeight / 100.0);
	}
	else {
		//return boxModelHeight;
		if (this->name == "root") {
			return boxModelHeight;
		}
		return boxModelHeight * this->yscale;
	}
}

int Element::GetContentWidth() {
	return this->contentSize.x;
}

int Element::GetContentHeight() {
	return this->contentSize.y;
}

int Element::GetBorderTop() {
	int topBorder = this->boxModel.border.top;
	if (this->boxModel.border.mode == PERCENTAGE) {
		return this->GetBoxHeight() * (topBorder / 100.0);
	}
	else {
		return topBorder;
	}
}

int Element::GetBorderBottom() {
	int bottomBorder = this->boxModel.border.bottom;
	if (this->boxModel.border.mode == PERCENTAGE) {
		return this->GetBoxHeight() * (bottomBorder / 100.0);
	}
	else {
		return bottomBorder;
	}
}

int Element::GetBorderLeft() {
	int leftBorder = this->boxModel.border.left;
	if (this->boxModel.border.mode == PERCENTAGE) {
		return this->GetBoxWidth() * (leftBorder / 100.0);
	}
	else {
		return leftBorder;
	}
}

int Element::GetBorderRight() {
	int rightBorder = this->boxModel.border.right;
	if (this->boxModel.border.mode == PERCENTAGE) {
		return this->GetBoxWidth() * (rightBorder / 100.0);
	}
	else {
		return rightBorder;
	}
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

	std::cout << "OVERFLOW: " << std::endl;
	if (this->overflow == HIDDEN)
		std::cout << "HIDDEN" << std::endl;
	else if (this->overflow == VISIBLE)
		std::cout << "HIDDEN" << std::endl;
	else
		std::cout << "ERROR: enum " << this->overflow << " for overflwo does not exist" << std::endl;

	std::cout << "Alignment: " << std::endl;
	if (this->alignment == VERTICAL)
		std::cout << "VERTICAL" << std::endl;
	else
		std::cout << "HORIZONTAL" << std::endl;

	std::cout << "position (x,y):" << std::endl;
	std::cout << this->boxPosition.x << ", " << this->boxPosition.y << std::endl;

	std::cout << "size (width, height):" << std::endl;
	std::cout << this->boxSize.x << ", " << this->boxSize.y << std::endl;

	std::cout << "borderPosition (x,y):" << std::endl;
	std::cout << this->borderPosition.x << ", " << this->borderPosition.y << std::endl;

	std::cout << "borderSize (width, height):" << std::endl;
	std::cout << this->borderSize.x << ", " << this->borderSize.y << std::endl;

	std::cout << "parent (width, height):" << std::endl;
	std::cout << this->parentWidth << ", " << this->parentHeight << std::endl;

	std::cout << "ContentPosition: (" << this->contentPosition.x << ", " << this->contentPosition.y << ")" << ", " << "ContentSize: (" << this->contentSize.x << ", " << this->contentSize.y << ")" << std::endl;

	std::cout << "rotation:" << std::endl;
	std::cout << this->rotation << std::endl;

	std::cout << "radius:" << std::endl;
	std::cout << this->radius << std::endl;

	std::cout << "borderRadius:" << std::endl;
	std::cout << this->borderRadius << std::endl;

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
	std::cout << "childrenWidthWithMargins: " << this->childrenWidthWithMargins << " childrenHeightWithMargins: " << this->childrenHeightWithMargins << std::endl;
	std::cout << "AlignContent: ";
	if (this->alignContent == CENTER_CONTENT)
		std::cout << "CENTER_CONTENT";
	else if (this->alignContent == START)
		std::cout << "START";
	else if (this->alignContent == END)
		std::cout << "END";
	std::cout << std::endl;

	std::cout << "AlignItems: ";
	if (this->alignItems == CENTER_ITEMS)
		std::cout << "CENTER_ITEMS";
	else if (this->alignItems == START_ITEMS)
		std::cout << "START_ITEMS";
	else if (this->alignItems == END_ITEMS)
		std::cout << "END_ITEMS";
	std::cout << std::endl;

	std::cout << std::endl;
	std::cout << "BoxModel Info:" << std::endl;
	this->boxModel.PrintInfo();
	std::cout << std::endl;
}

void Element::PrintPositioning() {
	std::cout << "PositionType: " << std::endl;
	if (this->positioning.positioningType == STATIC_POSITION) {
		std::cout << "STATIC" << std::endl;
	}
	else if (this->positioning.positioningType == RELATIVE_POSITION) {
		std::cout << "RELATIVE" << std::endl;
	}
	else if (this->positioning.positioningType == ABSOLUTE_POSITION) {
		std::cout << "ABSOLUTE" << std::endl;
	}
	else if (this->positioning.positioningType == FIXED_POSITION) {
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

void Element::PrintBorderCornerCoords() {
	std::cout << "borderPosition (x,y):" << std::endl;
	std::cout << this->borderPosition.x << ", " << this->borderPosition.y << std::endl;

	std::cout << "borderSize (width, height):" << std::endl;
	std::cout << this->borderSize.x << ", " << this->borderSize.y << std::endl;

	std::cout << "topLeft (x,y):" << std::endl;
	std::cout << "(" << this->borderTopLeft.x << ", " << this->borderTopLeft.y << ")" << std::endl;

	std::cout << "topRight (x,y):" << std::endl;
	std::cout << "(" << this->borderTopRight.x << ", " << this->borderTopRight.y << ")" << std::endl;

	std::cout << "bottomLeft (x,y):" << std::endl;
	std::cout << "(" << this->borderBottomLeft.x << ", " << this->borderBottomLeft.y << ")" << std::endl;

	std::cout << "bottomRight (x,y):" << std::endl;
	std::cout << "(" << this->borderBottomRight.x << ", " << this->borderBottomRight.y << ")" << std::endl;
}

void Element::PrintChildren() {
	Element* currChild = this->headChild;
	while (currChild != nullptr) {
		std::cout << currChild->name << std::endl;
		currChild = currChild->childAfter;
	}
}

void Element::PrintChildrenWidthAndHeight() {
	std::cout << "With margins (width, height):" << std::endl;
	std::cout << "    " << this->childrenWidthWithMargins << ", " << this->childrenHeightWithMargins << std::endl;
	std::cout << "Without margins (width, height):" << std::endl;
	std::cout << "    " << this->childrenWidth << ", " << this->childrenHeight << std::endl;
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

		if (curr->positioning.positioningType == STATIC_POSITION || curr->positioning.positioningType == RELATIVE_POSITION) {
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
	while (curr->positioning.positioningType == FIXED_POSITION || curr->positioning.positioningType == ABSOLUTE_POSITION) {
		if (curr->childBefore == nullptr) {
			std::cout << "ERROR::ELEMENT GetInlineChildBefore(): Somehow no element before this one is STATIC or RELATIVE." << std::endl;
			return nullptr;
		}
		curr = curr->childBefore;
	}
	return curr;
}

int Element::GetNumInlineChildren() {
	if (this->headChild == nullptr) return 0;
	int num = 0;
	Element* curr = this->headChild;
	while (curr != nullptr) {
		if (curr->positioning.positioningType == STATIC_POSITION || curr->positioning.positioningType == RELATIVE_POSITION) {
			num++;
		}
		curr = curr->childAfter;
	}
	return num;
}

void Element::CalculateBorderPosition()
{
	if (this->parent == nullptr) {
		//std::cout << "this->parent == nullptr" << std::endl;
		this->CalculateBorderPositionRoot();
		return;
	}
	else if (this->parent->alignment == HORIZONTAL) {
		//std::cout << "alignment == horizontal" << std::endl;
		this->CalculateBorderPositionHorizontal();
	}
	else if (this->parent->alignment == VERTICAL) {
		//std::cout << "alignment == vertical" << std::endl;
		this->CalculateBorderPositionVertical();
	}
}

// set up so margin and border do not affect root top left being at (0,0)
void Element::CalculateBorderPositionRoot()
{
	int xOffset = 0;
	int yOffset = 0;
	// if the element is root
	if (this->parent == nullptr) {
		this->boxPosition.x = 0;
		this->boxPosition.y = 0;
		this->borderPosition.x = 0 - this->GetBorderLeft();
		this->borderPosition.y = 0 - this->GetBorderTop();
	}
	else {
		std::cout << "ERROR::Element::CalculateBorderPositionRoot() This should only be being called on the root who has no parent but this element has a parent." << std::endl;
	}
}

// TODO: switch this over to work for the BorderPosition instead of BoxPosition
void Element::CalculateBorderPositionHorizontal()
{
	if (this->positioning.positioningType == ABSOLUTE_POSITION || this->positioning.positioningType == FIXED_POSITION) {
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
			this->borderPosition.x = parentContentX;
			//this->boxPosition.x = parentContentX;
		}
		else if (this->parent->alignContent == CENTER_CONTENT) {
			int childrenWidthWithMargins = this->parent->childrenWidthWithMargins;
			int parentWidth = this->parent->GetContentWidth();

			int childrenCenter = childrenWidthWithMargins / 2;
			int parentCenter = parentWidth / 2;

			int childrenStartX = parentContentX + parentCenter - childrenCenter;

			this->borderPosition.x = childrenStartX;
			//this->boxPosition.y = parentContentY;

		}
		else if (this->parent->alignContent == END) {
			int childrenWidthWithMargins = this->parent->childrenWidthWithMargins;
			int parentWidth = this->parent->GetContentWidth();


			int childrenStartX = parentContentX + parentWidth - childrenWidthWithMargins;

			this->borderPosition.x = childrenStartX;
			//this->boxPosition.y = parentContentY;

		}
		else if (this->parent->alignContent == SPACE_EVENLY) {
			int childrenWidth = this->parent->childrenWidth;
			int parentContentWidth = this->parent->GetContentWidth();
			int numInlineChildren = this->parent->GetNumInlineChildren();
			int spacing = (parentContentWidth - childrenWidth) / (numInlineChildren + 1);
			if (spacing < 0) {
				spacing = 0;
			}
			this->borderPosition.x = parentContentX + spacing;
		}
		else if (this->parent->alignContent == SPACE_BETWEEN) {
			int childrenWidth = this->parent->childrenWidth;
			int parentContentWidth = this->parent->GetContentWidth();
			int numInlineChildren = this->parent->GetNumInlineChildren();
			int spacing = (parentContentWidth - childrenWidth) / (numInlineChildren - 1);
			if (spacing < 0) {
				spacing = 0;
			}
			this->borderPosition.x = parentContentX;
		}
		else if (this->parent->alignContent == SPACE_AROUND) {
			int childrenWidth = this->parent->childrenWidth;
			int parentContentWidth = this->parent->GetContentWidth();
			int numInlineChildren = this->parent->GetNumInlineChildren();
			int spacing = (parentContentWidth - childrenWidth) / (numInlineChildren + 3);
			if (spacing < 0) {
				spacing = 0;
			}
			this->borderPosition.x = parentContentX + spacing * 2;
		}
		else {
			this->borderPosition.x = parentContentX;
			//this->boxPosition.y = parentContentY;
		}

		// set box position y value
		if (this->parent->alignItems == START_ITEMS) {
			this->borderPosition.y = parentContentY;
		}
		else if (this->parent->alignItems == CENTER_ITEMS) {
			int parentOffset = (this->parent->contentSize.y - this->borderSize.y) / 2;
			//if (parentOffset < 0) parentOffset = 0;
			//int yOffset = (maxHeight - this->boxSize.y) / 2;
			this->borderPosition.y = parentContentY + parentOffset;

		}
		else if (this->parent->alignItems == END_ITEMS) {
			int parentOffset = this->parent->contentSize.y - this->borderSize.y;
			this->borderPosition.y = parentContentY + parentOffset;

		}
		else {
			this->borderPosition.y = parentContentY;
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
			if (this->parent->alignContent == SPACE_EVENLY) {
				int childrenWidth = this->parent->childrenWidth;
				int parentContentWidth = this->parent->GetContentWidth();
				int numInlineChildren = this->parent->GetNumInlineChildren();
				int spacing = (parentContentWidth - childrenWidth) / (numInlineChildren + 1);
				if (spacing < 0) {
					spacing = 0;
				}
				this->borderPosition.x = childBefore->borderPosition.x + childBefore->borderSize.x + spacing;
			}
			else if (this->parent->alignContent == SPACE_BETWEEN) {
				int childrenWidth = this->parent->childrenWidth;
				int parentContentWidth = this->parent->GetContentWidth();
				int numInlineChildren = this->parent->GetNumInlineChildren();
				int spacing = (parentContentWidth - childrenWidth) / (numInlineChildren - 1);
				if (spacing < 0) {
					spacing = 0;
				}
				this->borderPosition.x = childBefore->borderPosition.x + childBefore->borderSize.x + spacing;
			}
			else if (this->parent->alignContent == SPACE_AROUND) {
				int childrenWidth = this->parent->childrenWidth;
				int parentContentWidth = this->parent->GetContentWidth();
				int numInlineChildren = this->parent->GetNumInlineChildren();
				int spacing = (parentContentWidth - childrenWidth) / (numInlineChildren + 3);
				if (spacing < 0) {
					spacing = 0;
				}
				this->borderPosition.x = childBefore->borderPosition.x + childBefore->borderSize.x + spacing;
			}
			else {
				int margin = (childBefore->GetMarginRight() > this->GetMarginLeft()) ? childBefore->GetMarginRight() : this->GetMarginLeft();
				int posX = childBefore->borderPosition.x + childBefore->borderSize.x + margin;
				this->borderPosition.x = posX;
			}

			if (this->parent->alignItems == START_ITEMS) {
				this->borderPosition.y = childBefore->borderPosition.y;
			}
			else if (this->parent->alignItems == CENTER_ITEMS) {
				int parentOffset = (this->parent->contentSize.y - this->borderSize.y) / 2;
				//if (parentOffset < 0) parentOffset = 0;
				//int yOffset = (maxHeight - this->boxSize.y) / 2;
				this->borderPosition.y = parentContentY + parentOffset;
			}
			else if (this->parent->alignItems == END_ITEMS) {
				int parentOffset = this->parent->contentSize.y - this->borderSize.y;
				this->borderPosition.y = parentContentY + parentOffset;
			}
			else {
				this->borderPosition.y = parentContentY;
			}

		}
	}
}

void Element::CalculateBorderPositionVertical()
{
	if (this->positioning.positioningType == ABSOLUTE_POSITION || this->positioning.positioningType == FIXED_POSITION) {
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
			this->borderPosition.y = parentContentY;
		}
		else if (this->parent->alignContent == CENTER_CONTENT) {
			int childrenHeightWithMargins = this->parent->childrenHeightWithMargins;
			int parentHeight = this->parent->GetContentHeight();

			int childrenCenter = childrenHeightWithMargins / 2;
			int parentCenter = parentHeight / 2;

			int childrenStartY = parentContentY + parentCenter - childrenCenter;

			this->borderPosition.y = childrenStartY;

		}
		else if (this->parent->alignContent == END) {
			int childrenHeightWithMargins = this->parent->childrenHeightWithMargins;
			int parentHeight = this->parent->GetContentHeight();


			int childrenStartY = parentContentY + parentHeight - childrenHeightWithMargins;

			this->borderPosition.y = childrenStartY;

		}
		else if (this->parent->alignContent == SPACE_EVENLY) {
			int childrenHeight = this->parent->childrenHeight;
			int parentContentHeight = this->parent->GetContentHeight();
			int numInlineChildren = this->parent->GetNumInlineChildren();
			int spacing = (parentContentHeight - childrenHeight) / (numInlineChildren + 1);
			if (spacing < 0) {
				spacing = 0;
			}
			this->borderPosition.y = parentContentY + spacing;
		}
		else if (this->parent->alignContent == SPACE_BETWEEN) {
			int childrenHeight = this->parent->childrenHeight;
			int parentContentHeight = this->parent->GetContentHeight();
			int numInlineChildren = this->parent->GetNumInlineChildren();
			int spacing = (parentContentHeight - childrenHeight) / (numInlineChildren - 1);
			if (spacing < 0) {
				spacing = 0;
			}
			this->borderPosition.y = parentContentY;
		}
		else if (this->parent->alignContent == SPACE_AROUND) {
			int childrenHeight = this->parent->childrenHeight;
			int parentContentHeight = this->parent->GetContentHeight();
			int numInlineChildren = this->parent->GetNumInlineChildren();
			int spacing = (parentContentHeight - childrenHeight) / (numInlineChildren + 3);
			if (spacing < 0) {
				spacing = 0;
			}
			this->borderPosition.y = parentContentY + spacing * 2;
		}
		else {
			this->borderPosition.y = parentContentY;
		}

		// set box position for x 
		if (this->parent->alignItems == START_ITEMS) {
			this->borderPosition.x = parentContentX;
		}
		else if (this->parent->alignItems == CENTER_ITEMS) {
			int parentOffset = (this->parent->contentSize.x - this->borderSize.x) / 2;
			this->borderPosition.x = parentContentX + parentOffset;
		}
		else if (this->parent->alignItems == END_ITEMS) {
			int parentOffset = this->parent->contentSize.x - this->borderSize.x;
			this->borderPosition.x = parentContentX + parentOffset;

		}
		else {
			this->borderPosition.x = parentContentX;
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
			if (this->parent->alignContent == SPACE_EVENLY) {
				int childrenHeight = this->parent->childrenHeight;
				int parentContentHeight = this->parent->GetContentHeight();
				int numInlineChildren = this->parent->GetNumInlineChildren();
				int spacing = (parentContentHeight - childrenHeight) / (numInlineChildren + 1);
				if (spacing < 0) {
					spacing = 0;
				}
				this->borderPosition.y = childBefore->borderPosition.y + childBefore->borderSize.y + spacing;
			}
			else if (this->parent->alignContent == SPACE_BETWEEN) {
				int childrenHeight = this->parent->childrenHeight;
				int parentContentHeight = this->parent->GetContentHeight();
				int numInlineChildren = this->parent->GetNumInlineChildren();
				int spacing = (parentContentHeight - childrenHeight) / (numInlineChildren - 1);
				if (spacing < 0) {
					spacing = 0;
				}
				this->borderPosition.y = childBefore->borderPosition.y + childBefore->borderSize.y + spacing;
			}
			else if (this->parent->alignContent == SPACE_AROUND) {
				int childrenHeight = this->parent->childrenHeight;
				int parentContentHeight = this->parent->GetContentHeight();
				int numInlineChildren = this->parent->GetNumInlineChildren();
				int spacing = (parentContentHeight - childrenHeight) / (numInlineChildren + 3);
				if (spacing < 0) {
					spacing = 0;
				}
				this->borderPosition.y = childBefore->borderPosition.y + childBefore->borderSize.y + spacing;
			}
			else {
				int margin = (childBefore->GetMarginBottom() > this->GetMarginTop()) ? childBefore->GetMarginBottom() : this->GetMarginTop();
				int posY = childBefore->borderPosition.y + childBefore->borderSize.y + margin;

				this->borderPosition.y = posY;
			}
			if (this->parent->alignItems == START_ITEMS) {
				this->borderPosition.x = parentContentX;
			}
			else if (this->parent->alignItems == CENTER_ITEMS) {
				int parentOffset = (this->parent->contentSize.x - this->borderSize.x) / 2;
				//if (parentOffset < 0) parentOffset = 0;
				//int xOffset = (maxWidth - this->boxSize.x) / 2;
				this->borderPosition.x = parentContentX + parentOffset;
			}
			else if (this->parent->alignItems == END_ITEMS) {
				int parentOffset = this->parent->contentSize.x - this->borderSize.x;
				this->borderPosition.x = parentContentX + parentOffset;
			}
			else {
				this->borderPosition.x = parentContentX;
			}
		}
	}
}

void Element::CalculateBoxPositionBasedOnBorderPosition() {
	this->boxPosition.x = this->borderPosition.x + this->GetBorderLeft();
	this->boxPosition.y = this->borderPosition.y + this->GetBorderTop();
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

// TODO: adjust these to just place the position based on border position and offset it by left border width and top border width
void Element::CalculateBoxPositionRoot() {
	int xOffset = 0;
	int yOffset = 0;
	// if the element is root
	if (this->parent == nullptr) {

		xOffset = this->boxModel.border.left;
		yOffset = this->boxModel.border.top;

		// set box position
		this->boxPosition.x = this->borderPosition.x + xOffset;
		this->boxPosition.y = this->borderPosition.y + yOffset;
	}
}

void Element::CalculateBoxPositionHorizontal() {
	if (this->positioning.positioningType == ABSOLUTE_POSITION || this->positioning.positioningType == FIXED_POSITION) {
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
			int childrenWidthWithMargins = this->parent->childrenWidthWithMargins;
			int parentWidth = this->parent->GetContentWidth();

			int childrenCenter = childrenWidthWithMargins / 2;
			int parentCenter = parentWidth / 2;

			int childrenStartX = parentContentX + parentCenter - childrenCenter;

			this->boxPosition.x = childrenStartX;
			//this->boxPosition.y = parentContentY;

		}
		else if (this->parent->alignContent == END) {
			int childrenWidthWithMargins = this->parent->childrenWidthWithMargins;
			int parentWidth = this->parent->GetContentWidth();


			int childrenStartX = parentContentX + parentWidth - childrenWidthWithMargins;

			this->boxPosition.x = childrenStartX;
			//this->boxPosition.y = parentContentY;

		}
		else if (this->parent->alignContent == SPACE_EVENLY) {
			int childrenWidth = this->parent->childrenWidth;
			int parentContentWidth = this->parent->GetContentWidth();
			int numInlineChildren = this->parent->GetNumInlineChildren();
			int spacing = (parentContentWidth - childrenWidth) / (numInlineChildren + 1);
			if (spacing < 0) {
				spacing = 0;
			}
			this->boxPosition.x = parentContentX + spacing;
		}
		else if (this->parent->alignContent == SPACE_BETWEEN) {
			int childrenWidth = this->parent->childrenWidth;
			int parentContentWidth = this->parent->GetContentWidth();
			int numInlineChildren = this->parent->GetNumInlineChildren();
			int spacing = (parentContentWidth - childrenWidth) / (numInlineChildren - 1);
			if (spacing < 0) {
				spacing = 0;
			}
			this->boxPosition.x = parentContentX;
		}
		else if (this->parent->alignContent == SPACE_AROUND) {
			int childrenWidth = this->parent->childrenWidth;
			int parentContentWidth = this->parent->GetContentWidth();
			int numInlineChildren = this->parent->GetNumInlineChildren();
			int spacing = (parentContentWidth - childrenWidth) / (numInlineChildren + 3);
			if (spacing < 0) {
				spacing = 0;
			}
			this->boxPosition.x = parentContentX + spacing * 2;
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
			int parentOffset = (this->parent->contentSize.y - this->boxSize.y) / 2;
			//if (parentOffset < 0) parentOffset = 0;
			//int yOffset = (maxHeight - this->boxSize.y) / 2;
			this->boxPosition.y = parentContentY + parentOffset;

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
			if (this->parent->alignContent == SPACE_EVENLY) {
				int childrenWidth = this->parent->childrenWidth;
				int parentContentWidth = this->parent->GetContentWidth();
				int numInlineChildren = this->parent->GetNumInlineChildren();
				int spacing = (parentContentWidth - childrenWidth) / (numInlineChildren + 1);
				if (spacing < 0) {
					spacing = 0;
				}
				this->boxPosition.x = childBefore->boxPosition.x + childBefore->boxSize.x + spacing;
			}
			else if (this->parent->alignContent == SPACE_BETWEEN) {
				int childrenWidth = this->parent->childrenWidth;
				int parentContentWidth = this->parent->GetContentWidth();
				int numInlineChildren = this->parent->GetNumInlineChildren();
				int spacing = (parentContentWidth - childrenWidth) / (numInlineChildren - 1);
				if (spacing < 0) {
					spacing = 0;
				}
				this->boxPosition.x = childBefore->boxPosition.x + childBefore->boxSize.x + spacing;
			}
			else if (this->parent->alignContent == SPACE_AROUND) {
				int childrenWidth = this->parent->childrenWidth;
				int parentContentWidth = this->parent->GetContentWidth();
				int numInlineChildren = this->parent->GetNumInlineChildren();
				int spacing = (parentContentWidth - childrenWidth) / (numInlineChildren + 3);
				if (spacing < 0) {
					spacing = 0;
				}
				this->boxPosition.x = childBefore->boxPosition.x + childBefore->boxSize.x + spacing;
			}
			else {
				int margin = (childBefore->GetMarginRight() > this->GetMarginLeft()) ? childBefore->GetMarginRight() : this->GetMarginLeft();
				int posX = childBefore->boxPosition.x + childBefore->boxSize.x + margin;
				this->boxPosition.x = posX;
			}

			if (this->parent->alignItems == START_ITEMS) {
				this->boxPosition.y = childBefore->boxPosition.y;
			}
			else if (this->parent->alignItems == CENTER_ITEMS) {
				int parentOffset = (this->parent->contentSize.y - this->boxSize.y) / 2;
				//if (parentOffset < 0) parentOffset = 0;
				//int yOffset = (maxHeight - this->boxSize.y) / 2;
				this->boxPosition.y = parentContentY + parentOffset;
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
	if (this->positioning.positioningType == ABSOLUTE_POSITION || this->positioning.positioningType == FIXED_POSITION) {
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
			int childrenHeightWithMargins = this->parent->childrenHeightWithMargins;
			int parentHeight = this->parent->GetContentHeight();

			int childrenCenter = childrenHeightWithMargins / 2;
			int parentCenter = parentHeight / 2;

			int childrenStartY = parentContentY + parentCenter - childrenCenter;

			//this->boxPosition.x = parentContentX;
			this->boxPosition.y = childrenStartY;

		}
		else if (this->parent->alignContent == END) {
			int childrenHeightWithMargins = this->parent->childrenHeightWithMargins;
			int parentHeight = this->parent->GetContentHeight();


			int childrenStartY = parentContentY + parentHeight - childrenHeightWithMargins;

			//this->boxPosition.x = parentContentX;
			this->boxPosition.y = childrenStartY;

		}
		else if (this->parent->alignContent == SPACE_EVENLY) {
			int childrenHeight = this->parent->childrenHeight;
			int parentContentHeight = this->parent->GetContentHeight();
			int numInlineChildren = this->parent->GetNumInlineChildren();
			int spacing = (parentContentHeight - childrenHeight) / (numInlineChildren + 1);
			if (spacing < 0) {
				spacing = 0;
			}
			this->boxPosition.y = parentContentY + spacing;
		}
		else if (this->parent->alignContent == SPACE_BETWEEN) {
			int childrenHeight = this->parent->childrenHeight;
			int parentContentHeight = this->parent->GetContentHeight();
			int numInlineChildren = this->parent->GetNumInlineChildren();
			int spacing = (parentContentHeight - childrenHeight) / (numInlineChildren - 1);
			if (spacing < 0) {
				spacing = 0;
			}
			this->boxPosition.y = parentContentY;
		}
		else if (this->parent->alignContent == SPACE_AROUND) {
			int childrenHeight = this->parent->childrenHeight;
			int parentContentHeight = this->parent->GetContentHeight();
			int numInlineChildren = this->parent->GetNumInlineChildren();
			int spacing = (parentContentHeight - childrenHeight) / (numInlineChildren + 3);
			if (spacing < 0) {
				spacing = 0;
			}
			this->boxPosition.y = parentContentY + spacing * 2;
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
			int parentOffset = (this->parent->contentSize.x - this->boxSize.x) / 2;
			//if (parentOffset < 0) parentOffset = 0;
			//int xOffset = (maxWidth - this->boxSize.x) / 2;
			this->boxPosition.x = parentContentX + parentOffset;
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
			if (this->parent->alignContent == SPACE_EVENLY) {
				int childrenHeight = this->parent->childrenHeight;
				int parentContentHeight = this->parent->GetContentHeight();
				int numInlineChildren = this->parent->GetNumInlineChildren();
				int spacing = (parentContentHeight - childrenHeight) / (numInlineChildren + 1);
				if (spacing < 0) {
					spacing = 0;
				}
				this->boxPosition.y = childBefore->boxPosition.y + childBefore->boxSize.y + spacing;
			}
			else if (this->parent->alignContent == SPACE_BETWEEN) {
				int childrenHeight = this->parent->childrenHeight;
				int parentContentHeight = this->parent->GetContentHeight();
				int numInlineChildren = this->parent->GetNumInlineChildren();
				int spacing = (parentContentHeight - childrenHeight) / (numInlineChildren - 1);
				if (spacing < 0) {
					spacing = 0;
				}
				this->boxPosition.y = childBefore->boxPosition.y + childBefore->boxSize.y + spacing;
			}
			else if (this->parent->alignContent == SPACE_AROUND) {
				int childrenHeight = this->parent->childrenHeight;
				int parentContentHeight = this->parent->GetContentHeight();
				int numInlineChildren = this->parent->GetNumInlineChildren();
				int spacing = (parentContentHeight - childrenHeight) / (numInlineChildren + 3);
				if (spacing < 0) {
					spacing = 0;
				}
				this->boxPosition.y = childBefore->boxPosition.y + childBefore->boxSize.y + spacing;
			}
			else {
				int margin = (childBefore->GetMarginBottom() > this->GetMarginTop()) ? childBefore->GetMarginBottom() : this->GetMarginTop();
				int posY = childBefore->boxPosition.y + childBefore->boxSize.y + margin;

				this->boxPosition.y = posY;
			}
			if (this->parent->alignItems == START_ITEMS) {
				this->boxPosition.x = parentContentX;
			}
			else if (this->parent->alignItems == CENTER_ITEMS) {
				int parentOffset = (this->parent->contentSize.x - this->boxSize.x) / 2;
				//if (parentOffset < 0) parentOffset = 0;
				//int xOffset = (maxWidth - this->boxSize.x) / 2;
				this->boxPosition.x = parentContentX + parentOffset;
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

/*
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
			int childrenWidthWithMargins = this->parent->childrenWidthWithMargins;
			int parentWidth = this->parent->GetContentWidth();

			int childrenCenter = childrenWidthWithMargins / 2;
			int parentCenter = parentWidth / 2;

			int childrenStartX = parentContentX + parentCenter - childrenCenter;

			this->boxPosition.x = childrenStartX;
			//this->boxPosition.y = parentContentY;

		}
		else if (this->parent->alignContent == END) {
			int childrenWidthWithMargins = this->parent->childrenWidthWithMargins;
			int parentWidth = this->parent->GetContentWidth();


			int childrenStartX = parentContentX + parentWidth - childrenWidthWithMargins;

			this->boxPosition.x = childrenStartX;
			//this->boxPosition.y = parentContentY;

		}
		else if (this->parent->alignContent == SPACE_EVENLY) {
			int childrenWidth = this->parent->childrenWidth;
			int parentContentWidth = this->parent->GetContentWidth();
			int numInlineChildren = this->parent->GetNumInlineChildren();
			int spacing = (parentContentWidth - childrenWidth) / (numInlineChildren + 1);
			if (spacing < 0) {
				spacing = 0;
			}
			this->boxPosition.x = parentContentX + spacing;
		}
		else if (this->parent->alignContent == SPACE_BETWEEN) {
			int childrenWidth = this->parent->childrenWidth;
			int parentContentWidth = this->parent->GetContentWidth();
			int numInlineChildren = this->parent->GetNumInlineChildren();
			int spacing = (parentContentWidth - childrenWidth) / (numInlineChildren - 1);
			if (spacing < 0) {
				spacing = 0;
			}
			this->boxPosition.x = parentContentX;
		}
		else if (this->parent->alignContent == SPACE_AROUND) {
			int childrenWidth = this->parent->childrenWidth;
			int parentContentWidth = this->parent->GetContentWidth();
			int numInlineChildren = this->parent->GetNumInlineChildren();
			int spacing = (parentContentWidth - childrenWidth) / (numInlineChildren + 3);
			if (spacing < 0) {
				spacing = 0;
			}
			this->boxPosition.x = parentContentX + spacing * 2;
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
			int parentOffset = (this->parent->contentSize.y - this->boxSize.y) / 2;
			//if (parentOffset < 0) parentOffset = 0;
			//int yOffset = (maxHeight - this->boxSize.y) / 2;
			this->boxPosition.y = parentContentY + parentOffset;

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
			if (this->parent->alignContent == SPACE_EVENLY) {
				int childrenWidth = this->parent->childrenWidth;
				int parentContentWidth = this->parent->GetContentWidth();
				int numInlineChildren = this->parent->GetNumInlineChildren();
				int spacing = (parentContentWidth - childrenWidth) / (numInlineChildren + 1);
				if (spacing < 0) {
					spacing = 0;
				}
				this->boxPosition.x = childBefore->boxPosition.x + childBefore->boxSize.x + spacing;
			}
			else if (this->parent->alignContent == SPACE_BETWEEN) {
				int childrenWidth = this->parent->childrenWidth;
				int parentContentWidth = this->parent->GetContentWidth();
				int numInlineChildren = this->parent->GetNumInlineChildren();
				int spacing = (parentContentWidth - childrenWidth) / (numInlineChildren - 1);
				if (spacing < 0) {
					spacing = 0;
				}
				this->boxPosition.x = childBefore->boxPosition.x + childBefore->boxSize.x + spacing;
			}
			else if (this->parent->alignContent == SPACE_AROUND) {
				int childrenWidth = this->parent->childrenWidth;
				int parentContentWidth = this->parent->GetContentWidth();
				int numInlineChildren = this->parent->GetNumInlineChildren();
				int spacing = (parentContentWidth - childrenWidth) / (numInlineChildren + 3);
				if (spacing < 0) {
					spacing = 0;
				}
				this->boxPosition.x = childBefore->boxPosition.x + childBefore->boxSize.x + spacing;
			}
			else {
				int margin = (childBefore->GetMarginRight() > this->GetMarginLeft()) ? childBefore->GetMarginRight() : this->GetMarginLeft();
				int posX = childBefore->boxPosition.x + childBefore->boxSize.x + margin;
				this->boxPosition.x = posX;
			}
			
			if (this->parent->alignItems == START_ITEMS) {
				this->boxPosition.y = childBefore->boxPosition.y;
			}
			else if (this->parent->alignItems == CENTER_ITEMS) {
				int parentOffset = (this->parent->contentSize.y - this->boxSize.y) / 2;
				//if (parentOffset < 0) parentOffset = 0;
				//int yOffset = (maxHeight - this->boxSize.y) / 2;
				this->boxPosition.y = parentContentY + parentOffset;
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
			int childrenHeightWithMargins = this->parent->childrenHeightWithMargins;
			int parentHeight = this->parent->GetContentHeight();

			int childrenCenter = childrenHeightWithMargins / 2;
			int parentCenter = parentHeight / 2;

			int childrenStartY = parentContentY + parentCenter - childrenCenter;

			//this->boxPosition.x = parentContentX;
			this->boxPosition.y = childrenStartY;

		}
		else if (this->parent->alignContent == END) {
			int childrenHeightWithMargins = this->parent->childrenHeightWithMargins;
			int parentHeight = this->parent->GetContentHeight();


			int childrenStartY = parentContentY + parentHeight - childrenHeightWithMargins;

			//this->boxPosition.x = parentContentX;
			this->boxPosition.y = childrenStartY;

		}
		else if (this->parent->alignContent == SPACE_EVENLY) {
			int childrenHeight = this->parent->childrenHeight;
			int parentContentHeight = this->parent->GetContentHeight();
			int numInlineChildren = this->parent->GetNumInlineChildren();
			int spacing = (parentContentHeight - childrenHeight) / (numInlineChildren + 1);
			if (spacing < 0) {
				spacing = 0;
			}
			this->boxPosition.y = parentContentY + spacing;
		}
		else if (this->parent->alignContent == SPACE_BETWEEN) {
			int childrenHeight = this->parent->childrenHeight;
			int parentContentHeight = this->parent->GetContentHeight();
			int numInlineChildren = this->parent->GetNumInlineChildren();
			int spacing = (parentContentHeight - childrenHeight) / (numInlineChildren - 1);
			if (spacing < 0) {
				spacing = 0;
			}
			this->boxPosition.y = parentContentY;
		}
		else if (this->parent->alignContent == SPACE_AROUND) {
			int childrenHeight = this->parent->childrenHeight;
			int parentContentHeight = this->parent->GetContentHeight();
			int numInlineChildren = this->parent->GetNumInlineChildren();
			int spacing = (parentContentHeight - childrenHeight) / (numInlineChildren + 3);
			if (spacing < 0) {
				spacing = 0;
			}
			this->boxPosition.y = parentContentY + spacing * 2;
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
			int parentOffset = (this->parent->contentSize.x - this->boxSize.x) / 2;
			//if (parentOffset < 0) parentOffset = 0;
			//int xOffset = (maxWidth - this->boxSize.x) / 2;
			this->boxPosition.x = parentContentX + parentOffset;
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
			if (this->parent->alignContent == SPACE_EVENLY) {
				int childrenHeight = this->parent->childrenHeight;
				int parentContentHeight = this->parent->GetContentHeight();
				int numInlineChildren = this->parent->GetNumInlineChildren();
				int spacing = (parentContentHeight - childrenHeight) / (numInlineChildren + 1);
				if (spacing < 0) {
					spacing = 0;
				}
				this->boxPosition.y = childBefore->boxPosition.y + childBefore->boxSize.y + spacing;
			}
			else if (this->parent->alignContent == SPACE_BETWEEN) {
				int childrenHeight = this->parent->childrenHeight;
				int parentContentHeight = this->parent->GetContentHeight();
				int numInlineChildren = this->parent->GetNumInlineChildren();
				int spacing = (parentContentHeight - childrenHeight) / (numInlineChildren - 1);
				if (spacing < 0) {
					spacing = 0;
				}
				this->boxPosition.y = childBefore->boxPosition.y + childBefore->boxSize.y + spacing;
			}
			else if (this->parent->alignContent == SPACE_AROUND) {
				int childrenHeight = this->parent->childrenHeight;
				int parentContentHeight = this->parent->GetContentHeight();
				int numInlineChildren = this->parent->GetNumInlineChildren();
				int spacing = (parentContentHeight - childrenHeight) / (numInlineChildren + 3);
				if (spacing < 0) {
					spacing = 0;
				}
				this->boxPosition.y = childBefore->boxPosition.y + childBefore->boxSize.y + spacing;
			}
			else {
				int margin = (childBefore->GetMarginBottom() > this->GetMarginTop()) ? childBefore->GetMarginBottom() : this->GetMarginTop();
				int posY = childBefore->boxPosition.y + childBefore->boxSize.y + margin;

				this->boxPosition.y = posY;
			}
			if (this->parent->alignItems == START_ITEMS) {
				this->boxPosition.x = parentContentX;
			}
			else if (this->parent->alignItems == CENTER_ITEMS) {
				int parentOffset = (this->parent->contentSize.x - this->boxSize.x) / 2;
				//if (parentOffset < 0) parentOffset = 0;
				//int xOffset = (maxWidth - this->boxSize.x) / 2;
				this->boxPosition.x = parentContentX + parentOffset;
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
*/
// TODO: make the adjustments for RELATIVE, FIXED, ABSOLUTE
void Element::AdjustIfNonStatic() {
	if (this->positioning.positioningType == FIXED_POSITION) {
		this->CalculatePositionFixed();
	}
	else if (this->positioning.positioningType == RELATIVE_POSITION) {
		this->CalculatePositionRelative();
	}
	else if (this->positioning.positioningType == ABSOLUTE_POSITION) {
		this->CalculatePositionAbsolute();
	}
}

void Element::CalculatePositionRelative() {
	// yes they will interfere with eachother
	this->borderPosition.x += this->GetLeft();
	this->borderPosition.x -= this->GetRight();
	this->borderPosition.y += this->GetTop();
	this->borderPosition.y -= this->GetBottom();
}

void Element::CalculatePositionAbsolute() {
	Element* relativeOrAbsoluteParent = this->FindParentRelativeOrAbsolute();
	//std::cout << relativeOrAbsoluteParent->name << std::endl;
	glm::vec2 centeringOffsets = this->GetParentCenteringOffsets(relativeOrAbsoluteParent);
	std::cout << centeringOffsets.x << " " << centeringOffsets.y << std::endl;
	if (this->positioning.centerHorizontally == true) {
		this->borderPosition.x = centeringOffsets.x;
	}
	if (this->positioning.centerVertically == true) {
		this->borderPosition.y = centeringOffsets.y;
	}
	// the 4 positional movements which is distance from that edge
	if (this->positioning.left > -1) {
		int leftPixels = this->GetLeft(relativeOrAbsoluteParent);
		int width = this->borderSize.x;

		int parentLeftEdge = relativeOrAbsoluteParent->boxPosition.x;
		this->borderPosition.x = parentLeftEdge;
		this->borderPosition.x += leftPixels;
	}
	if (this->positioning.right > -1) {
		int rightPixels = this->GetRight(relativeOrAbsoluteParent);
		int width = this->borderSize.x;

		int parentRightEdge = relativeOrAbsoluteParent->boxPosition.x + relativeOrAbsoluteParent->boxSize.x;
		this->borderPosition.x = parentRightEdge - width;
		this->borderPosition.x -= rightPixels;
	}
	if (this->positioning.top > -1) {
		int topPixels = this->GetTop(relativeOrAbsoluteParent);
		int height = this->borderSize.y;

		int parentTopEdge = relativeOrAbsoluteParent->boxPosition.y;
		this->borderPosition.y = parentTopEdge;
		this->borderPosition.y += topPixels;
	}
	if (this->positioning.bottom > -1) {
		int bottomPixels = this->GetBottom(relativeOrAbsoluteParent);
		int height = this->borderSize.y;

		int parentBottomEdge = relativeOrAbsoluteParent->boxPosition.y + relativeOrAbsoluteParent->boxSize.y;
		this->borderPosition.y = parentBottomEdge - height;
		this->borderPosition.y -= bottomPixels;
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
	glm::vec2 centeringOffsets = this->GetCenteringOffsets();

	if (this->positioning.centerHorizontally == true) {
		this->borderPosition.x = centeringOffsets.x;
	}
	if (this->positioning.centerVertically == true) {
		this->borderPosition.y = centeringOffsets.y;
	}
	
	// the 4 positional movements which is distance from that edge
	if (this->positioning.left > -1) {
		int leftPixels = this->GetLeft();
		int width = this->borderSize.x;
		

		int parentLeftEdge = 0;
		this->borderPosition.x = parentLeftEdge;
		this->borderPosition.x += leftPixels;
	}
	if (this->positioning.right > -1) {
		int rightPixels = this->GetRight();
		int width = this->borderSize.x;
		int screenWidth = this->screenWidth;

		int parentRightEdge = screenWidth;
		this->borderPosition.x = parentRightEdge - width;
		this->borderPosition.x -= rightPixels;
	}
	if (this->positioning.top > -1) {
		int topPixels = this->GetTop();
		int height = this->borderSize.y;

		int parentTopEdge = 0;
		this->borderPosition.y = parentTopEdge;
		this->borderPosition.y += topPixels;
	}
	if (this->positioning.bottom > -1) {
		int bottomPixels = this->GetBottom();
		int height = this->borderSize.y;
		int screenHeight = this->screenHeight;

		int parentBottomEdge = screenHeight;
		this->borderPosition.y = parentBottomEdge - height;
		this->borderPosition.y -= bottomPixels;
	}
}

glm::vec2 Element::GetCenteringOffsets() {
	if (this->positioning.positioningType == FIXED_POSITION) {
		int screenWidth = this->screenWidth;
		int screenHeight = this->screenHeight;

		int halfWidth = screenWidth / 2;
		int halfHeight = screenHeight / 2;
		int posX = halfWidth - (this->borderSize.x / 2);
		int posY = halfHeight - (this->borderSize.y / 2);
		return glm::vec2(posX, posY);
	}

	return glm::vec2(0, 0);
}

glm::vec2 Element::GetParentCenteringOffsets(Element* parent) {

	int parentWidth = parent->boxSize.x;
	int parentHeight = parent->boxSize.y;
	int parentPosX = parent->boxPosition.x;
	int parentPosY = parent->boxPosition.y;

	int halfWidth = parentWidth / 2;
	int halfHeight = parentHeight / 2;
	int centerX = halfWidth + parentPosX;
	int centerY = halfHeight + parentPosY;

	int posX = centerX - (this->borderSize.x / 2);
	int posY = centerY - (this->borderSize.y / 2);
	return glm::vec2(posX, posY);
	
}

Element* Element::FindParentRelativeOrAbsolute() {
	if (this->parent == nullptr) return nullptr;

	Element* curr = this->parent;
	if (curr->parent == nullptr) return curr;
	while (curr != nullptr && curr->parent != nullptr ) {
		if (curr->positioning.positioningType == RELATIVE_POSITION || curr->positioning.positioningType == ABSOLUTE_POSITION) {
			return curr;
		}
		curr = curr->parent;
	}
	return curr;
}


void Element::SetPositioningType(PositioningType type)
{
	if (type == ABSOLUTE_POSITION) {
		this->positioning.positioningType = ABSOLUTE_POSITION;
		this->positioning.left = -1;
		this->positioning.right = -1;
		this->positioning.top = -1;
		this->positioning.bottom = -1;
	}
	else if (type == RELATIVE_POSITION) {
		this->positioning.positioningType = RELATIVE_POSITION;
	}
	else if (type == FIXED_POSITION) {
		this->positioning.positioningType = FIXED_POSITION;
		this->positioning.left = -1;
		this->positioning.right = -1;
		this->positioning.top = -1;
		this->positioning.bottom = -1;
	}
	else if (type == STATIC_POSITION) {
		this->positioning.positioningType = STATIC_POSITION;
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

int Element::GetTop(Element* parent) {
	if (this->positioning.mode == PIXELS) return this->positioning.top;

	int parentHeight = parent->boxSize.y;

	float percentage = (float)this->positioning.top / 100.0;
	return parentHeight * percentage;
}

int Element::GetBottom(Element* parent) {
	if (this->positioning.mode == PIXELS) return this->positioning.bottom;

	int parentHeight = parent->boxSize.y;

	float percentage = (float)this->positioning.bottom / 100.0;
	return parentHeight * percentage;
}

int Element::GetLeft(Element* parent) {
	if (this->positioning.mode == PIXELS) return this->positioning.left;

	int parentWidth = parent->boxSize.x;

	float percentage = (float)this->positioning.left / 100.0;
	return parentWidth * percentage;
}

int Element::GetRight(Element* parent) {
	if (this->positioning.mode == PIXELS) return this->positioning.right;

	int parentWidth = parent->boxSize.x;

	float percentage = (float)this->positioning.right / 100.0;
	return parentWidth * percentage;
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

void Element::CalculateBordersSize() {
	int width = this->GetBoxWidth();
	int height = this->GetBoxHeight();
	int top = this->GetBorderTop();
	int bottom = this->GetBorderBottom();
	int left = this->GetBorderLeft();
	int right = this->GetBorderRight();

	this->borderSize.x = width + left + right;
	this->borderSize.y = height + top + bottom;
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
	else if ( !this->hideableViaOverflow ) {
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

void Element::RenderBorder(BorderRenderer* borderRenderer) {
	if (this->parent == nullptr) {
		borderRenderer->DrawBox(ResourceManager::GetTexture("no_tex"), this->borderPosition, this->borderSize, this->borderTopLeft, this->borderTopRight, this->borderBottomLeft, this->borderBottomRight, this->GetBorderRadius(), glm::vec2(this->screenWidth, this->screenHeight), this->rotation, this->idColor);
	}
	else if (!this->hideableViaOverflow) {
		borderRenderer->DrawBox(ResourceManager::GetTexture("no_tex"), this->borderPosition, this->borderSize, this->borderTopLeft, this->borderTopRight, this->borderBottomLeft, this->borderBottomRight, this->GetBorderRadius(), glm::vec2(this->screenWidth, this->screenHeight), this->rotation, this->idColor);
	}
	else if (this->parent->overflow == HIDDEN) {
		//std::cout << "HIDDEN" << std::endl;
		//boxRenderer->DrawBox(ResourceManager::GetTexture("no_tex"), this->boxPosition, this->boxSize, this->rotation, this->idColor);
		borderRenderer->DrawBoxOverflowHidden(ResourceManager::GetTexture("no_tex"), this->borderPosition, this->borderSize, this->parent->contentPosition, this->parent->contentSize, this->theRealContentBorders, this->borderTopLeft, this->borderTopRight, this->borderBottomLeft, this->borderBottomRight, this->GetBorderRadius(), glm::vec2(this->screenWidth, this->screenHeight), this->rotation, this->idColor);
		//borderRenderer->DrawBox(ResourceManager::GetTexture("no_tex"), this->borderPosition, this->borderSize, this->borderTopLeft, this->borderTopRight, this->borderBottomLeft, this->borderBottomRight, this->GetBorderRadius(), glm::vec2(this->screenWidth, this->screenHeight), this->rotation, this->idColor);
	}
	else {
		//std::cout << "VISIBLE" << std::endl;
		borderRenderer->DrawBox(ResourceManager::GetTexture("no_tex"), this->borderPosition, this->borderSize, this->borderTopLeft, this->borderTopRight, this->borderBottomLeft, this->borderBottomRight, this->GetBorderRadius(), glm::vec2(this->screenWidth, this->screenHeight), this->rotation, this->idColor);
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
	else if (!this->hideableViaOverflow) {
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
			if (curr->positioning.positioningType == FIXED_POSITION || curr->positioning.positioningType == ABSOLUTE_POSITION) { // these are not taken into account for the width and height
				curr = curr->childAfter;
				continue; 
			}
			width += curr->boxSize.x;
			if (curr->childAfter != nullptr) {
				// get both margins
				int nextMargin = curr->childAfter->GetMarginLeft();
				int currMargin = curr->GetMarginRight();
				int currRightBorder = curr->GetBorderRight();
				int nextLeftBorder = curr->childAfter->GetBorderLeft();
				width += (currMargin > nextMargin) ? currMargin : nextMargin;
				width += currRightBorder + nextLeftBorder;
			}
			curr = curr->childAfter;
		}
	}
	else if (this->alignment == VERTICAL) {
		Element* curr = this->headChild;
		while (curr != nullptr) {
			if (curr->positioning.positioningType == FIXED_POSITION || curr->positioning.positioningType == ABSOLUTE_POSITION) { // these are not taken into account for the width and height
				curr = curr->childAfter;
				continue;
			}			
			int currWidth = curr->boxSize.x + curr->GetBorderLeft() + curr->GetBorderRight();
			if (currWidth > width) {
				width = currWidth;
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
			int currHeight = curr->boxSize.y + curr->GetBorderTop() + curr->GetBorderBottom();
			if (currHeight > height) {
				height = currHeight;
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
				int currBorderBottom = curr->GetBorderBottom();
				int nextBorderTop = curr->childAfter->GetBorderTop();
				height += (currMargin > nextMargin) ? currMargin : nextMargin;
				height += currBorderBottom + nextBorderTop;
			}
			curr = curr->childAfter;
		}
	}
	this->childrenHeightWithMargins = height;
}

void Element::CalculateChildrenHeight() {
	if (this->headChild == nullptr) {
		this->childrenHeight = 0;
	}
	int height = 0;
	if (this->alignment == HORIZONTAL) {
		Element* curr = this->headChild;
		while (curr != nullptr) {
			if (curr->positioning.positioningType == FIXED_POSITION || curr->positioning.positioningType == ABSOLUTE_POSITION) { // these are not taken into account for the width and height
				curr = curr->childAfter;
				continue;
			}
			int currHeight = curr->boxSize.y + curr->GetBorderTop() + curr->GetBorderBottom();
			if (currHeight > height) {
				height = currHeight;
			}
			curr = curr->childAfter;
		}
	}
	else if (this->alignment == VERTICAL) {
		Element* curr = this->headChild;
		while (curr != nullptr) {
			if (curr->positioning.positioningType == FIXED_POSITION || curr->positioning.positioningType == ABSOLUTE_POSITION) { // these are not taken into account for the width and height
				curr = curr->childAfter;
				continue;
			}
			height += curr->boxSize.y + curr->GetBorderTop() + curr->GetBorderBottom();
			curr = curr->childAfter;
		}
	}
	this->childrenHeight = height;
}

void Element::CalculateChildrenWidth() {
	if (this->headChild == nullptr) {
		this->childrenWidth = 0;
	}
	int width = 0;
	if (this->alignment == HORIZONTAL) {
		Element* curr = this->headChild;
		while (curr != nullptr) {
			if (curr->positioning.positioningType == FIXED_POSITION || curr->positioning.positioningType == ABSOLUTE_POSITION) { // these are not taken into account for the width and height
				curr = curr->childAfter;
				continue;
			}
			int currWidth = curr->boxSize.x + curr->GetBorderLeft() + curr->GetBorderRight();
			width += currWidth;
			curr = curr->childAfter;
		}
	}
	else if (this->alignment == VERTICAL) {
		Element* curr = this->headChild;
		while (curr != nullptr) {
			if (curr->positioning.positioningType == FIXED_POSITION || curr->positioning.positioningType == ABSOLUTE_POSITION) { // these are not taken into account for the width and height
				curr = curr->childAfter;
				continue;
			}
			int currWidth = curr->boxSize.x + curr->GetBorderLeft() + curr->GetBorderRight();
			if (currWidth > width) {
				width = currWidth;
			}
			curr = curr->childAfter;
		}
	}
	this->childrenWidth = width;
}



// borders being boundaries for HIDDEN visibility
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

void Element::SetContentScale(float xscale, float yscale)
{
	this->xscale = xscale;
	this->yscale = yscale;
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

void Element::SetBorderRadius()
{
	this->borderRadius = this->radius + this->boxModel.border.left;
}

void Element::SetBorderRadius(int radius) {
	this->borderRadius = radius;
}

void Element::CalculateBorderCornerCoords() {
	int width = this->borderSize.x;
	int height = this->borderSize.y;

	int smallSide = (width < height) ? width : height;

	int maxRadius = this->borderRadius;
	if (this->borderRadius > smallSide / 2) {
		maxRadius = smallSide / 2;
	}
	// set top left coord currently not screen coords
	this->borderTopLeft.x = this->borderPosition.x + maxRadius;
	this->borderTopLeft.y = this->borderPosition.y + maxRadius;

	// set top right
	this->borderTopRight.x = this->borderPosition.x + width - maxRadius;
	this->borderTopRight.y = this->borderPosition.y + maxRadius;

	// set bottomLeft
	this->borderBottomLeft.x = this->borderPosition.x + maxRadius;
	this->borderBottomLeft.y = this->borderPosition.y + height - maxRadius;

	// set bottomRight
	this->borderBottomRight.x = this->borderPosition.x + width - maxRadius;
	this->borderBottomRight.y = this->borderPosition.y + height - maxRadius;

	// convert to screen coords
	this->borderTopLeft.x = (this->borderTopLeft.x / this->screenWidth) * 2 - 1;
	this->borderTopLeft.y = ((this->screenHeight - this->borderTopLeft.y) / this->screenHeight) * 2 - 1;

	
	this->borderTopRight.x = (this->borderTopRight.x / this->screenWidth) * 2 - 1;
	this->borderTopRight.y = ((this->screenHeight - this->borderTopRight.y) / this->screenHeight) * 2 - 1;

	this->borderBottomLeft.x = (this->borderBottomLeft.x / this->screenWidth) * 2 - 1;
	this->borderBottomLeft.y = ((this->screenHeight - this->borderBottomLeft.y) / this->screenHeight) * 2 - 1;

	this->borderBottomRight.x = (this->borderBottomRight.x / this->screenWidth) * 2 - 1;
	this->borderBottomRight.y = ((this->screenHeight - this->borderBottomRight.y) / this->screenHeight) * 2 - 1;

}

float Element::GetBorderRadius() {
	int width = this->borderSize.x;
	int height = this->borderSize.y;

	int smallSide = (width < height) ? width : height;

	int maxRadius = this->borderRadius;
	if (this->borderRadius > smallSide / 2) {
		maxRadius = smallSide / 2;
	}
	//std::cout << maxRadius << std::endl;
	//return (float)((maxRadius / this->screenWidth) * 2 - 1);
	return (float)maxRadius;
}