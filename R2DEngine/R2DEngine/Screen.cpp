#include "Screen.h"

using namespace rb;

int rb::Screen::width;
int rb::Screen::height;

int rb::Screen::Width()
{
	return width;
}
int rb::Screen::Height()
{
	return height;
}
float rb::Screen::WidthToFloat()
{
	return static_cast<float>(width);
}

float rb::Screen::HeightToFloat()
{
	return static_cast<float>(height);
}

rb::Vec2 rb::Screen::Center()
{
	return Vec2(WidthToFloat()*0.5f, HeightToFloat()*0.5f);
}

rb::Vec2 rb::Screen::ToWorldCoords(const Vec2& screenPosition)
{
	return Vec2(screenPosition.x, HeightToFloat() - screenPosition.y);
}

