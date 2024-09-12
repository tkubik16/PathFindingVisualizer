#ifndef ELEMENT_H
#define ELEMENT_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "box_model.h"
#include "box_renderer.h"

class Element
{
public:
	// basic data
	glm::vec3 idColor;
	BoxModel boxModel;
	std::string name;
	Element* parent;
	int parentWidth;
	int parentHeight;
	std::vector<Element*> children;
	// data that will get calculated later based on parent and sibling relations
	glm::vec2 boxPosition;
	glm::vec2 contentPosition;
	// x is width and y is height
	glm::vec2 boxSize;
	glm::vec2 contentSize;
	float rotation;

	Element();
	Element(std::string name);
	~Element();
	void PrintInfo();
	void SetChildrensParentDimensions();
	void SetParentDimensions(int width, int height);
	void CalculatePositions();
	void CalculateSize();
	void SetFillWidth();
	void SetFillHeight();
	void AddChild(Element* child);
	void RenderBox(BoxRenderer* boxRenderer);

};


#endif