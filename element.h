#ifndef ELEMENT_H
#define ELEMENT_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "box_model.h"
#include "box_renderer.h"
#include "content_box_renderer.h"
#include "border_renderer.h"



// The mode in which width and height gets calculated (How the value will be translated)
enum Alignment {
	VERTICAL,
	HORIZONTAL 
};

enum AlignContent {
	CENTER_CONTENT,
	START,
	END,
	SPACE_BETWEEN,
	SPACE_AROUND,
	SPACE_EVENLY
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

/*
space - between
The items are evenly distributed within the alignment container along the main axis.
The spacing between each pair of adjacent items is the same.The first item is flush 
with the main - start edge, and the last item is flush with the main - end edge.

space - around
The items are evenly distributed within the alignment container along the main axis.
The spacing between each pair of adjacent items is the same.The empty space before the 
first and after the last item equals half of the space between each pair of adjacent 
items.If there is only one item, it will be centered.

space - evenly
The items are evenly distributed within the alignment container along the main axis.
The spacing between each pair of adjacent items, the main - start edge and the first 
item, and the main - end edge and the last item, are all exactly the same.
*/

/*
enum Spacing {
	SPACE_BETWEEN,
	SPACE_AROUND,
	SPACE_EVENLY
};
*/

// FIXED and ABSOLUTE will be placed in the FreeElement list for a render pass after the Document Tree
enum PositioningType {
	STATIC,
	RELATIVE,
	FIXED,	
	ABSOLUTE
};

/*

~static

This is the default for every single page element. Different elements don’t have 
different default values for positioning, they all start out as static. Static doesn’t
mean much; it just means that the element will flow into the page as it normally would.
The only reason you would ever set an element to position: static; is to forcefully 
remove some positioning that got applied to an element outside of your control. This is
fairly rare, as positioning doesn’t cascade.

~relative

This type of positioning is probably the most confusing and misused. What it really means 
is “relative to itself”. If you set position: relative; on an element but no other 
positioning attributes (top, left, bottom or right), it will have no effect on it’s positioning
at all, it will be exactly as it would be if you left it as position: static; But if you do give
it some other positioning attribute, say, top: 10px;, it will shift its position 10 pixels
down from where it would normally be. I’m sure you can imagine, the ability to shift an element 
around based on its regular position is pretty useful. I find myself using this to line up form 
elements many times that have a tendency to not want to line up how I want them to.

~absolute

This is a very powerful type of positioning that allows you to literally place 
any page element exactly where you want it. You use the positioning attributes 
top, left, bottom, and right to set the location. Remember that these values will 
be relative to the next parent element with relative (or absolute) positioning. If 
there is no such parent, it will default all the way back up to the <html> element 
itself meaning it will be placed relative to the page itself.

The trade-off (and most important thing to remember) about absolute positioning is that 
these elements are removed from the flow of elements on the page. An element with this 
type of positioning is not affected by other elements and it doesn’t affect other elements.
This is a serious thing to consider every time you use absolute positioning. Its overuse or 
improper use can limit the flexibility of your site.

~fixed

A fixed position element is positioned relative to the viewport, or the browser window 
itself. The viewport doesn’t change when the window is scrolled, so a fixed positioned 
element will stay right where it is when the page is scrolled.

This might be used for something like a navigation bar that you want to remain visible at
all times regardless of the pages scroll position. The concern with fixed positioning is 
that it can cause situations where the fixed element overlaps content such that is is 
inaccessible. The trick is having enough space to avoid that, and tricks like this.
*/

struct Positioning {

	Positioning() : positioningType(STATIC), top(0), bottom(0), left(0), right(0), centerHorizontally(false), centerVertically(false), mode(PIXELS)
	{

	}

	~Positioning() {

	}
	// variables for positioning
	PositioningType positioningType;
	int top;
	int bottom;
	int left;
	int right;
	bool centerVertically;
	bool centerHorizontally;
	Mode mode;

	void PrintPositioning() {
		std::cout << "Positioning:\n";
		std::cout << "    PositioningType: ";
		if (this->positioningType == STATIC) {
			std::cout << "STATIC" << std::endl;
		}
		else if (this->positioningType == RELATIVE) {
			std::cout << "RELATIVE" << std::endl;
		}
		else if (this->positioningType == ABSOLUTE) {
			std::cout << "ABSOLUTE" << std::endl;
		}
		else if (this->positioningType == FIXED) {
			std::cout << "FIXED" << std::endl;
		}
		else {
			std::cout << "ERROR: enum " << this->positioningType << " does not exist." << std::endl;
		}
		std::cout << "    Top: " << this->top << std::endl;
		std::cout << "    Bottom: " << this->bottom << std::endl;
		std::cout << "    Left: " << this->left << std::endl;
		std::cout << "    Right: " << this->right << std::endl;
		std::cout << "    CenterVertically: " << this->centerVertically << std::endl;
		std::cout << "    CenterHorizontally: " << this->centerHorizontally << std::endl;
		std::cout << "    Mode: ";
		if (this->mode == PERCENTAGE) {
			std::cout << "PERCENTAGE" << std::endl;
		}
		else if (this->mode == PIXELS) {
			std::cout << "PIXELS" << std::endl;
		}
		else {
			std::cout << "ERROR: enum " << this->mode << " does not exist." << std::endl;
		}
	}

};

class Element
{
public:
	// basic data
	glm::vec3 idColor;
	BoxModel boxModel;
	std::string name;
	std::string className;
	int zIndex;
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
	glm::vec2 borderPosition;
	glm::vec2 boxPosition;
	glm::vec2 contentPosition;
	// x is width and y is height
	glm::vec2 borderSize;
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
	int childrenWidthWithMargins;
	int childrenHeightWithMargins;
	// children overflow hidden or not 
	Overflow overflow;
	bool hideableViaOverflow;
	// Positioning
	Positioning positioning;
	// corner radius
	int radius;
	int borderRadius;
	glm::vec2 topLeft;
	glm::vec2 topRight;
	glm::vec2 bottomLeft;
	glm::vec2 bottomRight;
	glm::vec2 borderTopLeft;
	glm::vec2 borderTopRight;
	glm::vec2 borderBottomLeft;
	glm::vec2 borderBottomRight;
	

	Element();
	Element(std::string name);
	~Element();
	// print methods
	void PrintInfo();
	void PrintBorders();
	void PrintRealBorders();
	void PrintCornerCoords();
	void PrintBorderCornerCoords();
	void PrintPositioning();
	void PrintChildrenWidthAndHeight();


	void SetChildrensParentDimensions();
	void SetParentDimensions(int width, int height);
	void CalculatePositions();
	void CalculateBorderPosition();
	void CalculateBorderPositionRoot();
	void CalculateBorderPositionHorizontal();
	void CalculateBorderPositionVertical();
	void CalculateBoxPositionBasedOnBorderPosition();
	void CalculateBoxPosition();
	void CalculateBoxPositionRoot();
	void CalculateBoxPositionHorizontal();
	void CalculateBoxPositionVertical();
	void CalculateContentPosition();
	
	void CalculateBordersSize();
	void CalculateContentSize();
	void CalculateBoxSize();
	// to be used for space between and space around adn space evenly
	void CalculateChildrenWidth();
	void CalculateChildrenHeight();
	int GetNumInlineChildren();

	void CalculateChildrenWidthWithMargins();
	void CalculateChildrenHeightWithMargins();
	void SetFillWidth();
	void SetFillHeight();
	void AddChild(Element* child);
	void AddChildToVector(Element* child);
	void RenderBox(BoxRenderer* boxRenderer);
	void RenderBorder(BorderRenderer* borderRenderer);
	void RenderContentBox(ContentBoxRenderer* contentBoxRenderer);
	void RenderContentBox(ContentBoxRenderer* contentBoxRenderer, bool wireframe);
	void PrintChildren();
	glm::vec4 CalculateBorders();
	void FindRealContentBorders();
	void SetChildrensParentContentBorders(glm::vec4 borders);

	void SetScreenSize(int width, int height);

	// methods for RELATIVE, FIXED, ABSOLUTE
	void AdjustIfNonStatic();
	void CalculatePositionRelative();
	void CalculatePositionFixed();
	void CalculatePositionAbsolute();
	void CenterHorizontal(); 
	void CenterVertical();
	glm::vec2 GetCenteringOffsets();
	Element* FindParentRelativeOrAbsolute();
	glm::vec2 GetParentCenteringOffsets(Element* parent);


	// corner radius methods
	void SetRadius(int radius);
	void CalculateCornerCoords();
	float GetRadius();

	// border corner radius methods
	void SetBorderRadius();
	void SetBorderRadius(int radius);
	void CalculateBorderCornerCoords();
	float GetBorderRadius();

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
	int GetBorderTop();
	int GetBorderBottom();
	int GetBorderLeft();
	int GetBorderRight();

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

	//Positioning methods
	void SetPositioningType(PositioningType type);
	int GetTop();
	int GetBottom();
	int GetLeft();
	int GetRight();
	int GetTop(Element* parent);
	int GetBottom(Element* parent);
	int GetLeft(Element* parent);
	int GetRight(Element* parent);


private:
	


};


#endif