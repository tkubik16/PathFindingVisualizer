#include <iostream>

#include "framebuffer.h"

Framebuffer::Framebuffer(int width, int height) : screenWidth(width), screenHeight(height), fbo(0), texture(0)
{
	std::cout << "Framebuffer: " << width << ", " << height << std::endl;
}

Framebuffer::~Framebuffer() {
	glDeleteFramebuffers(1, &(this->fbo));;
}

void Framebuffer::Init() {
	glGenFramebuffers(1, &(this->fbo));

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &(this->texture));
	glBindTexture(GL_TEXTURE_2D, this->texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->screenWidth, this->screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "FRAMEBUFFER::SUCCESS framebuffer complete" << std::endl;
	}
	else {
		std::cout << "FRAMEBUFFER::ERROR framebuffer incomplete" << std::endl;
	}

	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
	// unbind fbo
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::UpdateScreenSize(int width, int height) {
	this->screenWidth = width;
	this->screenHeight = height;

	glBindTexture(GL_TEXTURE_2D, this->texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->screenWidth, this->screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Framebuffer::Bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
}

void Framebuffer::Unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}