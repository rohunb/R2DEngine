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
		if (!loop && currFrame + 1 >= numFrames)
		{
			animationComplete = true;
			return;
		}
		currFrame = ++currFrame % numFrames;
		gridPos = Vec2(currFrame % sheetWidth, currFrame / sheetWidth);
		currentTime = 0.0f;
	}
	currentTime += dt;
}

void rb::SpriteAnimator::SetShaderValues(Shader& shader)
{
	shader.SetVec4("uFrameInfo", Vec4(static_cast<float>(sheetWidth), static_cast<float>(sheetHeight), gridPos.x, gridPos.y));
}
bool rb::SpriteAnimator::IsAnimationComplete() const
{
	return animationComplete;
}
