#ifndef BOX_MODEL
#define BOX_MODEL

#include <glad/glad.h>
#include <glm/glm.hpp>


#include <iostream>

// The mode in which width and height gets calculated (How the value will be translated)
enum Mode {
	PERCENTAGE,
	PIXELS
};

struct Content {
	Content(int width, int height, Mode mode) : width(width), height(height), mode(mode)
	{

	}

	~Content() {
	}

	void Print() {
		std::cout << this->width << " " << this->height << " " << this->mode;
	}

	int width;
	int height;
	Mode mode;
};

struct Padding {
	Padding(int top, int bottom, int left, int right, Mode mode) : top(top), bottom(bottom), left(left), right(right), mode(mode)
	{

	}

	~Padding() {

	}

	int top;
	int bottom;
	int left;
	int right;
	Mode mode;
};

struct Border {
	Border(int top, int bottom, int left, int right, Mode mode) : top(top), bottom(bottom), left(left), right(right), mode(mode)
	{

	}

	~Border() {

	}
	int top;
	int bottom;
	int left;
	int right;
	Mode mode;
};

struct Margin {
	Margin(int top, int bottom, int left, int right, Mode mode) : top(top), bottom(bottom), left(left), right(right), mode(mode)
	{

	}

	~Margin() {

	}
	int top;
	int bottom;
	int left;
	int right;
	Mode mode;
};

class BoxModel
{
public:
	// object data
	Content content;
	Padding padding;
	Border border;
	Margin margin;

	// Constructor/destructor
	BoxModel();
	~BoxModel();
	// object functions TBD
	// calcualting overall width and height for rendering
	void PrintInfo();
};

#endif