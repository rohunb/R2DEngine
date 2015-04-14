#include "AnimatedSprite.h"

using namespace rb;

rb::AnimatedSprite::AnimatedSprite(const Texture& spriteSheet, int sheetWidth, int sheetHeight, int numCells, float frameDuration, bool loop)
	:spriteSheet(spriteSheet), sheetWidth(sheetWidth), sheetHeight(sheetHeight), numCells(numCells), frameDuration(frameDuration), loop(loop)
{

}

void rb::AnimatedSprite::InitGL()
{

}
