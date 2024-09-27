#include <iostream>
#include <sstream>

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
		//std::cout << "FRAMEBUFFER::SUCCESS framebuffer complete" << std::endl;
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

std::string Framebuffer::Sample(double x, double y) {
	
	//std::cout << x << " " << y << std::endl;
	this->Bind();
	unsigned char pixel[4];
	glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixel);
	this->Unbind();
	//std::cout << "SampledPixel" << std::endl;
	//std::cout << (float)pixel[0] / 255 << ", " << (float)pixel[1] / 255 << ", " << (float)pixel[2] / 255 << ", " << (float)pixel[3] / 255 << std::endl;
	// TODO: get the main to call a function in program.cpp which calls this program with the appropriate coordinates that were clicked on
	float r = (float)pixel[0] / 255;
	float g = (float)pixel[1] / 255;
	float b = (float)pixel[2] / 255;
	float a = (float)pixel[3] / 255;
	//std::cout << "rgb: " << r << "," << g << "," << b << "," << a << std::endl;
	std::ostringstream ss;
	ss << this->Round(r) << "," << this->Round(g) << "," << this->Round(b);
	std::string s(ss.str());
	//std::cout << s << std::endl;
	return s;
}

float Framebuffer::Round(float var) {
	//std::cout << var << std::endl;
	float value = (int)(var * 100 + .5);
	return (float)value / 100;
}