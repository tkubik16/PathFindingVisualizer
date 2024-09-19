#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <map>

#include "element.h"
#include "renderers.h"
#include "box_renderer.h"
#include "content_box_renderer.h"

class Document
{
public:
	// map of color Ids to element pointers to know what element the mouse pointer is interacting with based on color of pixel in special frame buffer
	std::map<std::string, Element*> colorIdMap;
	Element* root;
	int screenWidth;
	int screenHeight;
	bool randomColors;

	// constructor/destructor
	Document();
	Document(int width, int height);
	~Document();

	void Init();
	Element* AddElement(std::string name);
	bool ColorIdExists(glm::vec3 colorId);
	void SetAllElementsSizes();
	void SetAllElementsPositions();
	void RenderDocumentFromVectors(Renderers* renderers);
	void RenderDocument(Renderers* renderers);
	void RenderDocument(BoxRenderer* boxRenderer);
	void RenderDocument(ContentBoxRenderer* contentBoxRenderer);
	void UpdateRootToScreenSize(int screenWidth, int screenHeight);
	void Update();

};


#endif