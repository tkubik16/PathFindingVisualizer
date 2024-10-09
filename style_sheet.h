#ifndef STYLE_SHEET_H
#define STYLE_SHEET_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <map>

#include "element.h"
#include "style.h"

class StyleSheet
{
public:
	std::map<std::string, Style*> styleMap;

	StyleSheet();
	~StyleSheet();
	void Init();
	void AddStyle(std::string name);
	Style* GetStyle(std::string name);
	void SetStyle(std::string name, Element* element);
	void Print(std::string name);
};

#endif
