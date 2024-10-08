#include "style_sheet.h"

StyleSheet::StyleSheet() {

}

StyleSheet::~StyleSheet() {

}

void StyleSheet::Init() {
	this->AddStyle("testStyle");

}

void StyleSheet::AddStyle(std::string name) {
	this->styleMap[name] = new Style(name);
}

void StyleSheet::SetStyle(std::string name, Element* element)
{
}

void StyleSheet::Print(std::string name) {
	if (this->styleMap.count(name) <= 0) {
		std::cout << "ERROR::StyleSheet::Print(std::string name): style with name: \"" << name << "\" does not exist." << std::endl;
		return;
	}
	Style* style = this->styleMap[name];
	style->PrintStyle();
}