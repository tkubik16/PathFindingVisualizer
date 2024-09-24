#ifndef ELEMENT_H
#define ELEMENT_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "box_model.h"
#include "box_renderer.h"
#include "content_box_renderer.h"

// The mode in which width and height gets calculated (How the value will be translated)
enum Alignment {
	VERTICAL,
	HORIZONTAL 
};

enum AlignContent {
	CENTER_CONTENT,
	START,
	END
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

class Element
{
public:
	// basic data
	glm::vec3 idColor;
	BoxModel boxModel;
	std::string name;
	Element* parent;
	Element* childBefore;
	Element* childAfter;
	int parentWidth;
	int parentHeight;
	int screenWidth;
	int screenHeight;
	glm::vec4 parentContentBorders;
	glm::vec4 theRealContentBorders;
	std::vector<Element*> children;
	Element* headChild;
	Element* tailChild;
	// data that will get calculated later based on parent and sibling relations
	glm::vec2 boxPosition;
	glm::vec2 contentPosition;
	// x is width and y is height
	glm::vec2 boxSize;
	glm::vec2 contentSize;
	float rotation;
	// Children info
	// for cetner, left, or right aligning of elements in the parent content
	AlignContent alignContent;
	AlignItems alignItems;
	// for horizontal or vertical element layout
	Alignment alignment; 
	int childrenWidth;
	int childrenHeight;
	// children overflow hidden or not 
	Overflow overflow;

	Element();
	Element(std::string name);
	~Element();
	void PrintInfo();
	void PrintBorders();
	void PrintRealBorders();
	void SetChildrensParentDimensions();
	void SetParentDimensions(int width, int height);
	void CalculatePositions();
	void CalculateBoxPosition();
	void CalculateBoxPositionRoot();
	void CalculateBoxPositionHorizontal();
	void CalculateBoxPositionVertical();
	void CalculateContentPosition();
	void CalculateContentSize();
	void CalculateBoxSize();
	void CalculateChildrenWidth();
	void CalculateChildrenHeight();
	void SetFillWidth();
	void SetFillHeight();
	void AddChild(Element* child);
	void AddChildToVector(Element* child);
	void RenderBox(BoxRenderer* boxRenderer);
	void RenderContentBox(ContentBoxRenderer* contentBoxRenderer);
	void RenderContentBox(ContentBoxRenderer* contentBoxRenderer, bool wireframe);
	void PrintChildren();
	glm::vec4 CalculateBorders();
	void FindRealContentBorders();
	void SetChildrensParentContentBorders(glm::vec4 borders);

	void SetScreenSize(int width, int height);

	// methods for Setting Mode
	void SetBoxWidthMode(Mode mode);
	void SetBoxHeightMode(Mode mode);
	void SetPaddingMode(Mode mode);
	void SetMarginMode(Mode mode);
	void SetBorderMode(Mode mode);

	int GetContentWidth();
	int GetContentHeight();

	// methods for Getting pixel equivalents when Mode is PERCENTAGE 
	int GetBoxWidth();
	int GetBoxHeight();

	// methods for Getting pixel equivalents when Mode is PERCENTAGE 

	// These use the percentage of the elements box not the parent or screen
	int GetPaddingTop();
	int GetPaddingBottom();
	int GetPaddingLeft();
	int GetPaddingRight();

	int GetMarginTop();
	int GetMarginBottom();
	int GetMarginLeft();
	int GetMarginRight();


private:
	


};


#endif