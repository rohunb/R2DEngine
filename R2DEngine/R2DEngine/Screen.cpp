#include "Screen.h"

using namespace rb;


int rb::Screen::width;
int rb::Screen::height;

int rb::Screen::Width() const
{
	return width;
}
int rb::Screen::Height() const
{
	return height;
}

rb::Vec2 rb::Screen::ToWorldCoords(const Vec2& screenPosition)
{
	return Vec2(screenPosition.x, height - screenPosition.y);
}

