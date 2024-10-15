#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <map>

#include "element.h"
#include "renderers.h"
#include "box_renderer.h"
#include "content_box_renderer.h"
#include "style.h"

struct FixedElement {
	FixedElement(Element* el, int ind) : element(el), zIndex(ind)
	{

	}

	~FixedElement()
	{

	}

	Element* element;
	int zIndex;
};

class Document
{
public:
	// map of color Ids to element pointers to know what element the mouse pointer is interacting with based on color of pixel in special frame buffer
	std::map<std::string, Element*> colorIdMap;
	std::map<std::string, Element*> nameMap;
	Element* root;
	std::vector<FixedElement> fixedElements;
	int screenWidth;
	int screenHeight;
	float xscale, yscale;
	bool randomColors;

	// constructor/destructor
	Document();
	Document(int width, int height);
	~Document();

	void Init();
	Element* AddElement(std::string name);
	void AddFixedElement(Element* element);
	void UpdateFixedElementZIndex(Element* element);
	bool ColorIdExists(glm::vec3 colorId);
	void SetAllElementsScreenSizes(int width, int height);
	void SetAllElementsSizes();
	void SetAllElementsPositions();
	void AdjustElementsIfNonStatic();
	void SetAllElementsChildrenWidthAndHeight();
	void SetAllElementsParentsContentBorders();
	void SetAllElementsRealContentBorders();
	void SetAllElementsCornerCoords();
	void SetAllElementsOverflowCornerCoords();
	void RenderDocumentFromVectors(Renderers* renderers);
	void RenderDocument(Renderers* renderers);
	void RenderDocument(BoxRenderer* boxRenderer);
	void RenderDocument(ContentBoxRenderer* contentBoxRenderer);
	void UpdateRootToScreenSize(int screenWidth, int screenHeight);
	void Update();

	// methods to get elements by name or className from the Document tree or map
	Element* GetElementByName(std::string elementName);
	Element* GetElementFromDocTree(std::string elementName);
	void StyleElementsWithClassNameInDocTree(std::string className, Style* style); // could make a classMap<std::string, Element*[]> 
};


#endif