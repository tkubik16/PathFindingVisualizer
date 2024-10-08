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
	
	
	Style(std::string styleName);
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
	void SetZIndex(int zIndex);
	void SetRotation(float rotation);
	void SetRadius(int radius);
	void SetBorderRadius(int borderRadius);
	void SetAlignContent(AlignContent alignContent);
	void SetAlignItems(AlignItems alignItems);
	void SetAlignment(Alignment alignment);
	void SetOverflow(Overflow overflow);
	void SetOverflowHideable(bool value);
	void SetPositioning(PositioningType positioningType, int top, int bottom, int left, int right, bool centerVertically, bool centerHorizontally, Mode mode);

	/*
	PositioningType positioningType;
	int top;
	int bottom;
	int left;
	int right;
	bool centerVertically;
	bool centerHorizontally;
	Mode mode;
	*/


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
	int borderRadius;
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