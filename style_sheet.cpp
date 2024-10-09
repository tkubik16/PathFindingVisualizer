#include "style_sheet.h"

StyleSheet::StyleSheet() {

}

StyleSheet::~StyleSheet() {

}

void StyleSheet::Init() {
	this->AddStyle("testStyle");

}

void StyleSheet::AddStyle(std::string name) {
	if (this->styleMap.count(name) > 0) {
		std::cout << "ERROR::StyleSheet::AddStyle(std::string name): Style with the name \"" << name << "\" already exists in the StyleSheet" << std::endl;
		return;
	}
	this->styleMap[name] = new Style(name);
}

void StyleSheet::SetStyle(std::string name, Element* element)
{
	Style* style = this->GetStyle(name);
	if (style == nullptr) return;

	// TODO: set all the memebers in element to the memebers in style
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