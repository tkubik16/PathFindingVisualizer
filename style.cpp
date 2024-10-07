
#include "style.h"

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
	radius(0)
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

