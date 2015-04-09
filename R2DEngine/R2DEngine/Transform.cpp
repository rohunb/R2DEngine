#include "Transform.h"
#include "GameObject.h"
#include "RDebug.h"

using namespace rb;

rb::Transform::Transform(const Vec2& position, const Vec2& size, float rotation)
	: position(position), size(size), rotation(rotation)
{
}

rb::Transform::Transform()
	: Transform(Vec2(0.0f), Vec2(1.0f), 0.0f)
{}

