#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <map>

#include "element.h"

class Document
{
public:
	// map of color Ids to element pointers to know what element the mouse pointer is interacting with based on color of pixel in special frame buffer
	std::map<std::string, Element*> colorIdMap;
	Element* root;

	// constructor/destructor
	Document();
	Document(int width, int height);
	~Document();

	Element* CreateElement(std::string name);
	bool ColorIdExists(glm::vec3 colorId);

};


#endif