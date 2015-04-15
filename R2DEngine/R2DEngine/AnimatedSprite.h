#ifndef R_ANIMATED_SPRITE_H_
#define R_ANIMATED_SPRITE_H_

#include "R2DComponent.h"
#include "Texture.h"
#include "Shader.h"
#include "Colour.h"

namespace rb
{
	class AnimatedSprite// : public R2DComponent
	{
	public:
		AnimatedSprite()=default;
		AnimatedSprite(const Texture& spriteSheet, int sheetWidth, int sheetHeight, int numFrames, float frameDuration, bool loop);
		//default copy/move/dtors

		void Update(float dt);
		void Render();

	private:
		int sheetWidth, sheetHeight, numFrames, currFrame;
		float frameDuration, currentTime;
		Vec2 gridPos;
		bool loop;
		Shader shader;
		Texture spriteSheet;
		Colour colour;
		GLuint VAO;
		void InitGL();
	};
}

#endif // R_ANIMATED_SPRITE_H_