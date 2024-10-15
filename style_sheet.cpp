#include "style_sheet.h"

StyleSheet::StyleSheet() {

}

StyleSheet::~StyleSheet() {

}

void StyleSheet::Init() {
	Style* testStyle = this->AddStyle("testStyle");
	testStyle->SetClassName("testStylingClass");
	testStyle->SetWidthHeight(50, 50);
	testStyle->SetPadding(10);
	testStyle->SetBorder(1);
	testStyle->SetMargin(5);
	testStyle->SetRadius(5);
	
}

Style* StyleSheet::AddStyle(std::string name) {
	if (this->styleMap.count(name) > 0) {
		std::cout << "ERROR::StyleSheet::AddStyle(std::string name): Style with the name \"" << name << "\" already exists in the StyleSheet" << std::endl;
		return nullptr;
	}
	Style* style = new Style(name);
	this->styleMap[name] = style;

	return style;
}

void StyleSheet::SetStyle(std::string styleName, Element* element)
{	
	if (element == nullptr) {
		std::cout << "ERROR::StyleSheet::SetStyle(std::string styleName, Element* element): style " << "\"" << styleName << "\" does not exist." << std::endl;
		return;
	}

	Style* style = this->GetStyle(styleName);
	if (style == nullptr) {
		std::cout << "ERROR::StyleSheet::SetStyle(std::string styleName, Element* element): element is a nullptr." << std::endl;
		return;
	}

	style->StyleElement(element);
}

Style* StyleSheet::GetStyle(std::string name) {
	if (this->styleMap.count(name) < 1) {
		std::cout << "ERROR::StyleSheet::GetStyle(std::string name): StyleSheet does not containe style named \"" << name << "\"" << std::endl;
		return nullptr;
	}
	return this->styleMap[name];
}

void StyleSheet::Print(std::string name) {
	if (this->styleMap.count(name) <= 0) {
		std::cout << "ERROR::StyleSheet::Print(std::string name): style with name: \"" << name << "\" does not exist." << std::endl;
		return;
	}
	Style* style = this->styleMap[name];
	style->PrintStyle();
}