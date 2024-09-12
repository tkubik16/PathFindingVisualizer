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
	glm::vec2 position;
	// x is width and y is height
	glm::vec2 size;
	float rotation;

	Element();
	Element(std::string name);
	~Element();
	void PrintInfo();
	void SetParentDimensions(int width, int height);
	void CalculatePosition();
	void CalculateSize();
	void AddChild(Element* child);
	void RenderBox(BoxRenderer* boxRenderer);

};


#endif