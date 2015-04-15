#ifndef R_ANIMATED_SPRITE_H_
#define R_ANIMATED_SPRITE_H_

#include "R2DComponent.h"
#include "RVector.h"

namespace rb
{
	class SpriteAnimator : public R2DComponent
	{
	public:
		SpriteAnimator()=default;
		SpriteAnimator(int sheetWidth, int sheetHeight, int numFrames, float frameDuration, bool loop);
		//default copy/move/dtors

		bool IsAnimationComplete() const;

		void Initialize(int sheetWidth, int sheetHeight, int numFrames, float frameDuration, bool loop);
		void Update(float dt);
		
		//void Render();
		void SetShaderValues(class Shader& shader);

	private:
		int sheetWidth, sheetHeight, numFrames, currFrame;
		float frameDuration, currentTime;
		Vec2 gridPos;
		bool loop;
		bool animationComplete=false;
		/*Shader shader;
		Texture spriteSheet;
		Colour colour;
		GLuint VAO;*/
		//void InitGL();
	};
}

#endif // R_ANIMATED_SPRITE_H_