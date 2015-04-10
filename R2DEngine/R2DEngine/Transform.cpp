#include "Transform.h"
#include "GameObject.h"
#include "RDebug.h"

using namespace rb;

rb::Transform::Transform(const Vec2& position, float rotation, const Vec2& size)
	: position(position), rotation(rotation), size(size)
{
}

rb::Transform::Transform()
	: Transform(Vec2(0.0f), 0.0f, Vec2(1.0f))
{}

