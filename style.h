#ifndef STYLE_H
#define STYLE_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "box_model.h"
#include "element.h"

class Style
{
public:
	// style only data
	std::string styleName;
	// styleable data 
	//std::string name; // name should be unique maybe
	std::string className;
	BoxModel boxModel;
	int zIndex;
	float rotation;
	// corner radius
	int radius;
	// for center, left, or right aligning of elements in the parent content
	AlignContent alignContent;
	AlignItems alignItems;
	// for horizontal or vertical element layout
	Alignment alignment;
	// children overflow hidden or not 
	Overflow overflow;
	bool hideableViaOverflow;
	// Positioning
	Positioning positioning;
	

	Style(std::string styleName, std::string className);
	~Style();

	void PrintStyle();


};




#endif