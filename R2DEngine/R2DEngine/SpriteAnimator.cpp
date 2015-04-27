#include "SpriteAnimator.h"
#include "Shader.h"
#include "RDebug.h"

using namespace rb;

rb::SpriteAnimator::SpriteAnimator(int sheetWidth, int sheetHeight, int numFrames, float frameDuration, bool loop)
{
	Initialize(sheetWidth, sheetHeight, numFrames, frameDuration, loop);
}

void rb::SpriteAnimator::Initialize(int sheetWidth, int sheetHeight, int numFrames, float frameDuration, bool loop)
{
	assert(numFrames <= sheetWidth * sheetHeight && "Num Frames should not be greater than sprite sheet size");
	this->sheetWidth = sheetWidth;
	this->sheetHeight = sheetHeight;
	this->numFrames = numFrames;
	this->frameDuration = frameDuration;
	this->loop = loop;
	currFrame = 0;
	currentTime = 0.0f;
	animationComplete = false;
}

void rb::SpriteAnimator::Update(float dt)
{
	if (animationComplete) return;
	if (currentTime >= frameDuration)
	{
		const int frameIncrement = dt <= frameDuration ? 1 : 1;
		if (!loop && currFrame + frameIncrement >= numFrames)
		{
			animationComplete = true;
			return;
		}
		currFrame = (currFrame + frameIncrement) % numFrames;
		gridPos = Vec2(currFrame % sheetWidth, currFrame / sheetWidth);
		currentTime = 0.0f;
	}
	currentTime += dt;
}

void rb::SpriteAnimator::SetShaderValues(Shader& shader)
{
	//Debug::Log("Grid pos" + ToString(gridPos));
	shader.SetVec4("uFrameInfo", Vec4(static_cast<float>(sheetWidth), static_cast<float>(sheetHeight), gridPos.x, gridPos.y));
}
bool rb::SpriteAnimator::IsAnimationComplete() const
{
	return animationComplete;
}
