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

/*
struct Content {
	Content(int width, int height, Mode mode) : width(width), height(height), mode(mode)
	{

	}

	~Content() {
	}

	void Print() {
		std::cout << this->width << " " << this->height << " " << this->mode << std::endl;
	}

	int width;
	int height;
	Mode mode;
};
*/
struct Padding {
	Padding(int top, int bottom, int left, int right, Mode mode) : top(top), bottom(bottom), left(left), right(right), mode(mode)
	{

	}

	~Padding() {

	}

	void Print() {
		std::cout << this->top << " " << this->bottom << " " << this->left << " " << this->right << " " << this->mode << std::endl;
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

	void Print() {
		std::cout << this->top << " " << this->bottom << " " << this->left << " " << this->right << " " << this->mode << std::endl;
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

	void Print() {
		std::cout << this->top << " " << this->bottom << " " << this->left << " " << this->right << " " << this->mode << std::endl;
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
	//Content content;
	int width;
	int height;
	Padding padding;
	Border border;
	Margin margin;

	// Constructor/destructor
	BoxModel();
	~BoxModel();
	// object functions TBD
	// calcualting overall width and height for rendering
	void PrintInfo();
	// content setter functions
	//void SetContent(int width, int height);
	//void SetContent(int width, int height, Mode mode);
	void SetSize(int width, int height);
	// padding setter functions
	void SetPadding(int top, int bottom, int left, int right);
	void SetPaddingAll(int val);
	void SetPaddingTopBot(int val);
	void SetPaddingLeftRight(int val);
	// border setter functions
	void SetBorder(int top, int bottom, int left, int right);
	void SetBorderAll(int val);
	void SetBorderTopBot(int val);
	void SetBorderLeftRight(int val);
	// margin setter functions
	void SetMargin(int top, int bottom, int left, int right);
	void SetMarginAll(int val);
	void SetMarginTopBot(int val);
	void SetMarginLeftRight(int val);

};

#endif