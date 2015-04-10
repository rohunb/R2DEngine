#include "Texture.h"
#include "RDebug.h"

rb::Texture::Texture()
	:width(0), height(0), textureID(0)
{
}

void rb::Texture::GenerateGLTexture(int width, int height, unsigned char* imageData)
{
	this->width = width;
	this->height = height;
	glGenTextures(1, &textureID);
	Bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Unbind();
	//Debug::Log("Tex Width: " + ToString(width) + "," + ToString(height));
}

void rb::Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void rb::Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
