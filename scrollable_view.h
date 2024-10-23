#ifndef SCROLLABLE_VIEW_H
#define SCROLLABLE_VIEW_H

#include "element.h"

class ScrollableView : public Element
{

public:
	glm::mat4 projection;
	glm::mat4 view;


	ScrollableView(std::string name);
	~ScrollableView();


};


#endif