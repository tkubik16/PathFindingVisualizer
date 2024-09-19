#include <iostream>

#include "renderers.h"

Renderers::Renderers() {

}

Renderers::~Renderers() {
	delete this->boxRenderer;
	delete this->contentBoxRenderer;
	delete this->textureRenderer;
}