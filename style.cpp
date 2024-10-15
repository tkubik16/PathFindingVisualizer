
#include "style.h"

Style::Style(std::string styleName) :
	styleName(styleName),
	className(""),
	zIndex(1),
	rotation(0),
	alignContent(START),
	alignItems(START_ITEMS),
	alignment(VERTICAL),
	overflow(HIDDEN),
	hideableViaOverflow(true),
	radius(0),
	borderRadius(0)
{

}

Style::Style(std::string styleName, std::string className) :
	styleName(styleName),
	className(className),
	zIndex(1),
	rotation(0),
	alignContent(START),
	alignItems(START_ITEMS),
	alignment(VERTICAL),
	overflow(HIDDEN),
	hideableViaOverflow(true),
	radius(0),
	borderRadius(0)
{

}

Style::~Style() {

}

/*
enum Alignment {
	VERTICAL,
	HORIZONTAL
};

enum AlignContent {
	CENTER_CONTENT,
	START,
	END,
	SPACE_BETWEEN,
	SPACE_AROUND,
	SPACE_EVENLY
};

enum AlignItems {
	START_ITEMS,
	CENTER_ITEMS,
	END_ITEMS
};

enum Overflow {
	HIDDEN,
	VISIBLE
};
*/

void PrintAlignment(Alignment alignment) {
	if (alignment == VERTICAL) {
		std::cout << "VERTICAL" << std::endl;
	}
	else if (alignment == HORIZONTAL) {
		std::cout << "HORIZONTAL" << std::endl;
	}
}

void PrintAlignContent(AlignContent alignContent) {
	if (alignContent == CENTER_CONTENT) {
		std::cout << "CENTER_CONTENT" << std::endl;
	}
	else if (alignContent == START) {
		std::cout << "START" << std::endl;
	}
	else if (alignContent == END) {
		std::cout << "END" << std::endl;
	}
	else if (alignContent == SPACE_BETWEEN) {
		std::cout << "SPACE_BETWEEN" << std::endl;
	}
	else if (alignContent == SPACE_AROUND) {
		std::cout << "SPACE_AROUND" << std::endl;
	}
	else if (alignContent == SPACE_EVENLY) {
		std::cout << "SPACE_EVENLY" << std::endl;
	}
	else {
		std::cout << "ERROR: enum " << alignContent << " does not exist." << std::endl;
	}
}

void PrintOverflow(Overflow overflow) {
	if (overflow == HIDDEN) {
		std::cout << "HIDDEN" << std::endl;
	}
	else if (overflow == VISIBLE) {
		std::cout << "VISIBLE" << std::endl;
	}
	else {
		std::cout << "ERROR: enum " << overflow << " does not exist." << std::endl;
	}
}

void PrintAlignItems(AlignItems alignItems) {
	if (alignItems == START_ITEMS) {
		std::cout << "START_ITEMS" << std::endl;
	}
	else if (alignItems == CENTER_ITEMS) {
		std::cout << "CENTER_ITEMS" << std::endl;
	}
	else if (alignItems == END_ITEMS) {
		std::cout << "END_ITEMS" << std::endl;
	}
	else {
		std::cout << "ERROR: enum " << alignItems << " does not exist." << std::endl;
	}
}

void Style::PrintStyle() {
	std::cout << "Style name: " << this->styleName << std::endl;
	std::cout << "Class name: " << this->className << std::endl;
	this->boxModel.PrintInfo();
	std::cout << "Z-Index: " << this->zIndex << std::endl;
	std::cout << "Rotation: " << this->rotation << std::endl;
	std::cout << "Radius: " << this->radius << std::endl;
	std::cout << "BorderRadius: " << this->borderRadius << std::endl;
	std::cout << "Alignment: ";
	PrintAlignment(this->alignment);
	std::cout << "AlignContent: ";
	PrintAlignContent(this->alignContent);
	std::cout << "AlignItems: ";
	PrintAlignItems(this->alignItems);
	std::cout << "Overflow: ";
	PrintOverflow(this->overflow);
	std::cout << "HideableViewOverflow: " << this->hideableViaOverflow << std::endl;
	this->positioning.PrintPositioning();
}

void Style::SetStyleName(std::string name)
{
	this->styleName = name;
}

void Style::SetClassName(std::string name) {
	this->className = name;
}

void Style::SetWidth(int width) {
	this->boxModel.width = width;
}

void Style::SetHeight(int height) {
	this->boxModel.height = height;
}

void Style::SetWidthHeight(int width, int height)
{
	this->boxModel.width = width;
	this->boxModel.height = height;
}

void Style::SetBoxWidthMode(Mode mode) {
	this->boxModel.boxWidthMode = mode;
}

void Style::SetBoxHeightMode(Mode mode) {
	this->boxModel.boxHeightMode = mode;
}

void Style::SetPaddingMode(Mode mode) {
	this->boxModel.padding.mode = mode;
}

void Style::SetPadding(int padding) {
	this->boxModel.SetPaddingAll(padding);
}

void Style::SetPadding(int top, int bottom, int left, int right) {
	this->boxModel.padding.top = top;
	this->boxModel.padding.bottom = bottom;
	this->boxModel.padding.left = left;
	this->boxModel.padding.right = right;
}

void Style::SetBorderMode(Mode mode) {
	this->boxModel.border.mode = mode;
}

void Style::SetBorder(int border) {
	this->boxModel.SetBorderAll(border);
}

void Style::SetBorder(int top, int bottom, int left, int right) {
	this->boxModel.border.top = top;
	this->boxModel.border.bottom = bottom;
	this->boxModel.border.left = left;
	this->boxModel.border.right = right;
}

void Style::SetMarginMode(Mode mode) {
	this->boxModel.margin.mode = mode;
}

void Style::SetMargin(int margin) {
	this->boxModel.SetMarginAll(margin);
}

void Style::SetMargin(int top, int bottom, int left, int right) {
	this->boxModel.margin.top = top;
	this->boxModel.margin.bottom = bottom;
	this->boxModel.margin.left = left;
	this->boxModel.margin.right = right;
}

void Style::SetZIndex(int zIndex) {
	this->zIndex = zIndex;
}

void Style::SetRotation(float rotation) {
	this->rotation = rotation;
}

void Style::SetRadius(int radius) {
	this->radius = radius;
}

void Style::SetBorderRadius(int borderRadius) {
	this->borderRadius = borderRadius;
}

void Style::SetAlignContent(AlignContent alignContent) {
	this->alignContent = alignContent;
}

void Style::SetAlignItems(AlignItems alignItems) {
	this->alignItems = alignItems;
}

void Style::SetAlignment(Alignment alignment) {
	this->alignment = alignment;
}

void Style::SetOverflow(Overflow overflow) {
	this->overflow = overflow;
}

void Style::SetOverflowHideable(bool value) {
	this->hideableViaOverflow = value;
}

void Style::SetPositioning(PositioningType positioningType, int top, int bottom, int left, int right, bool centerVertically, bool centerHorizontally, Mode mode) {
	this->positioning.positioningType = positioningType;
	this->positioning.top = top;
	this->positioning.bottom = bottom;
	this->positioning.left = left;
	this->positioning.right = right;
	this->positioning.centerVertically = centerVertically;
	this->positioning.centerHorizontally = centerHorizontally;
	this->positioning.mode = mode;
}

void Style::StyleElementBoxModel(Element* element) {
	element->boxModel.width = this->boxModel.width;
	element->boxModel.height = this->boxModel.height;
	element->boxModel.boxWidthMode = this->boxModel.boxWidthMode;
	element->boxModel.boxHeightMode = this->boxModel.boxHeightMode;
	//padding
	element->boxModel.padding.top = this->boxModel.padding.top;
	element->boxModel.padding.bottom = this->boxModel.padding.bottom;
	element->boxModel.padding.left = this->boxModel.padding.left;
	element->boxModel.padding.right = this->boxModel.padding.right;
	element->boxModel.padding.mode = this->boxModel.padding.mode;
	//margin
	element->boxModel.margin.top = this->boxModel.margin.top;
	element->boxModel.margin.bottom = this->boxModel.margin.bottom;
	element->boxModel.margin.left = this->boxModel.margin.left;
	element->boxModel.margin.right = this->boxModel.margin.right;
	element->boxModel.margin.mode = this->boxModel.margin.mode;
	//border
	element->boxModel.border.top = this->boxModel.border.top;
	element->boxModel.border.bottom = this->boxModel.border.bottom;
	element->boxModel.border.left = this->boxModel.border.left;
	element->boxModel.border.right = this->boxModel.border.right;
	element->boxModel.border.mode = this->boxModel.border.mode;

}

void Style::StyleElementPositioning(Element* element)
{
	element->positioning.positioningType = this->positioning.positioningType;
	element->positioning.top = this->positioning.top;
	element->positioning.bottom = this->positioning.bottom;
	element->positioning.left = this->positioning.left;
	element->positioning.right = this->positioning.right;
	element->positioning.centerHorizontally = this->positioning.centerHorizontally;
	element->positioning.centerVertically = this->positioning.centerVertically;
	element->positioning.mode = this->positioning.mode;
}

void Style::StyleElement(Element* element)
{
	//std::cout << "styling: " << element->name << " " << element->className << " " << this->styleName << std::endl;
	element->className = this->className;
	element->zIndex = this->zIndex;
	element->rotation = this->rotation;
	element->radius = this->radius;
	element->borderRadius = this->borderRadius;
	element->alignContent = this->alignContent;
	element->alignItems = this->alignItems;
	element->alignment = this->alignment;
	element->overflow = this->overflow;
	element->hideableViaOverflow = this->hideableViaOverflow;

	//BoxModel
	this->StyleElementBoxModel(element);
	//Positioning
	this->StyleElementPositioning(element);

}


