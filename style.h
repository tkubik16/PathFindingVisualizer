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
	
	

	Style(std::string styleName, std::string className);
	~Style();

	void PrintStyle();

	void SetStyleName(std::string name);
	void SetClassName(std::string name);
	// boxmodel setters
	void SetWidth(int width);
	void SetHeight(int height);
	void SetBoxWidthMode(Mode mode);
	void SetBoxHeightMode(Mode mode);
	void SetPadding(int padding);
	void SetPadding(int top, int bottom, int left, int right);
	void SetBorder(int border);
	void SetBorder(int top, int bottom, int left, int right);
	void SetMargin(int border);
	void SetMargin(int top, int bottom, int left, int right);


private:
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
};




#endif