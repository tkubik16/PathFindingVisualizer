#include <iostream>

#include "renderers.h"

Renderers::Renderers() {

}

Renderers::~Renderers() {
	delete this->boxRenderer;
	delete this->contentBoxRenderer;
	delete this->textureRenderer;
}

void Renderers::SetScreenSize(int width, int height) {
	this->screenWidth = width;
	this->screenHeight = height;

	this->boxRenderer->SetScreenWidth(width);
	this->boxRenderer->SetScreenHeight(height);

	this->contentBoxRenderer->SetScreenWidth(width);
	this->contentBoxRenderer->SetScreenHeight(height);
}

void Renderers::SetScreenWidth(int width) {
	this->screenWidth = width;
}

void Renderers::SetScreenHeight(int height) {
	this->screenHeight = height;
}