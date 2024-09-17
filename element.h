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
	// Children alignment
	Alignment alignment;

	Element();
	Element(std::string name);
	~Element();
	void PrintInfo();
	void SetChildrensParentDimensions();
	void SetParentDimensions(int width, int height);
	void CalculatePositions();
	void CalculateBoxPosition();
	void CalculateContentPosition();
	void CalculateContentSize();
	void CalculateBoxSize();
	void SetFillWidth();
	void SetFillHeight();
	void AddChild(Element* child);
	void AddChildToVector(Element* child);
	void RenderBox(BoxRenderer* boxRenderer);
	void RenderContentBox(ContentBoxRenderer* contentBoxRenderer);
	void PrintChildren();


};


#endif