
#include <iostream>

#include "box_model.h"


BoxModel::BoxModel() :
	width(10),
	height(10),
	padding(0, 0, 0, 0, PIXELS), 
	border(0, 0, 0, 0, PIXELS), 
	margin(0, 0, 0, 0, PIXELS), 
	boxWidthMode(PIXELS), 
	boxHeightMode(PIXELS)
{

}

BoxModel::~BoxModel() {

}

void BoxModel::PrintInfo() {
	//std::cout << "content: ";
	//this->content.Print();
	//std::cout << std::endl;
	std::cout << "BoxModel:" << std::endl;
	std::cout << "    width: " << this->width << std::endl;
	std::cout << "    height: " << this->height << std::endl;
	std::cout << "    padding: ";
	this->padding.Print();
	std::cout << "    margin: ";
	this->margin.Print();
	std::cout << "    border: ";
	this->border.Print();
}

// Content setter functions
/*
void BoxModel::SetContent(int width, int height) {
	this->content.width = width;
	this->content.height = height;
}

void BoxModel::SetContent(int width, int height, Mode mode) {
	this->content.width = width;
	this->content.height = height;
	this->content.mode = mode;
}
*/

void BoxModel::SetSize(int width, int height) {
	this->width = width;
	this->height = height;
}

// Padding setter functions

void BoxModel::SetPadding(int top, int bottom, int left, int right) {
	this->padding.top = top;
	this->padding.bottom = bottom;
	this->padding.left = left;
	this->padding.right = right;
}
void BoxModel::SetPaddingAll(int val) {
	this->padding.top = val;
	this->padding.bottom = val;
	this->padding.left = val;
	this->padding.right = val;
}
void BoxModel::SetPaddingTopBot(int val) {
	this->padding.top = val;
	this->padding.bottom = val;
}
void BoxModel::SetPaddingLeftRight(int val) {
	this->padding.left = val;
	this->padding.right = val;
}

// Border setter functions

void BoxModel::SetBorder(int top, int bottom, int left, int right) {
	this->border.top = top;
	this->border.bottom = bottom;
	this->border.left = left;
	this->border.right = right;
}
void BoxModel::SetBorderAll(int val) {
	this->border.top = val;
	this->border.bottom = val;
	this->border.left = val;
	this->border.right = val;
}
void BoxModel::SetBorderTopBot(int val) {
	this->border.top = val;
	this->border.bottom = val;
}
void BoxModel::SetBorderLeftRight(int val) {
	this->border.left = val;
	this->border.right = val;
}

// Margin setter functions

void BoxModel::SetMargin(int top, int bottom, int left, int right) {
	this->margin.top = top;
	this->margin.bottom = bottom;
	this->margin.left = left;
	this->margin.right = right;
}
void BoxModel::SetMarginAll(int val) {
	this->margin.top = val;
	this->margin.bottom = val;
	this->margin.left = val;
	this->margin.right = val;
}
void BoxModel::SetMarginTopBot(int val) {
	this->margin.top = val;
	this->margin.bottom = val;
}
void BoxModel::SetMarginLeftRight(int val) {
	this->margin.left = val;
	this->margin.right = val;
}