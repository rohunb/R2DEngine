#ifndef R_ANIMATED_SPRITE_H_
#define R_ANIMATED_SPRITE_H_

#include "R2DComponent.h"
#include "Texture.h"
#include "Shader.h"
#include "Colour.h"

namespace rb
{
	class AnimatedSprite : public R2DComponent
	{
	public:
		AnimatedSprite()=default;
		AnimatedSprite(const Texture& spriteSheet, int sheetWidth, int sheetHeight, int numCells, float frameDuration, bool loop);
		//default copy/move/dtors

	private:
		int sheetWidth, sheetHeight, numCells;
		float frameDuration;
		bool loop;
		Shader shader;
		Texture spriteSheet;
		Colour colour;
		GLuint VAO;

		void InitGL();
	};
}

#endif // R_ANIMATED_SPRITE_H_