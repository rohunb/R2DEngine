#include "RVector.h"

using namespace rb;

rb::Vec2 rb::RVector2::up = Vec2(0.0f, 1.0f);
rb::Vec2 rb::RVector2::down = Vec2(0.0f, -1.0f);
rb::Vec2 rb::RVector2::right = Vec2(1.0f, 0.0f);
rb::Vec2 rb::RVector2::left = Vec2(-1.0f, 0.0f);

rb::Vec3 rb::RVector2::ToVector3(const Vec2& vec2)
{
	return Vec3(vec2, 0.0f);
}

Vec3 rb::RVector3::up = Vec3(0.0f, 1.0f, 0.0f);
Vec3 rb::RVector3::down = -up;
Vec3 rb::RVector3::left = Vec3(-1.0f, 0.0f, 0.0f);
Vec3 rb::RVector3::right = -left;
Vec3 rb::RVector3::forward = Vec3(0.0f, 0.0f, -1.0f);
Vec3 rb::RVector3::back = -forward;

rb::Vec2 rb::RVector3::ToVector2(const Vec3& vec3)
{
	return Vec2(vec3.x, vec3.y);
}
