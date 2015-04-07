#ifndef R_TEXTURE_H_
#define R_TEXTURE_H_

#include "GL_Includes.h"

namespace rb
{
	struct Texture
	{
		GLuint textureID;
		int width, height;
		Texture();
		void GenerateGLTexture(int width, int height, unsigned char* imageData);
		void Bind() const;
		static void Unbind();
	};
}

#endif // R_TEXTURE_H_
