#include "Texture.h"

rb::Texture::Texture()
	:width(0), height(0)
{
	glGenTextures(1, &textureID);
}

void rb::Texture::GenerateGLTexture(int width, int height, unsigned char* imageData)
{
	this->width = width;
	this->height = height;
	Bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Unbind();
}

void rb::Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void rb::Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
