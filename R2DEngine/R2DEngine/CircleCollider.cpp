#include "CircleCollider.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "SpriteRenderer.h"

using namespace rb;

rb::CircleCollider::CircleCollider()
	:CircleCollider(1.0f)
{}

rb::CircleCollider::CircleCollider(float radius)
	: radius(radius)
{
	Collider::type = ColliderType::Circle;
}

rb::CircleCollider::CircleCollider(const CircleCollider& rhs)
	: radius(rhs.radius)
{}
CircleCollider& rb::CircleCollider::operator=(const CircleCollider& rhs)
{
	radius = rhs.radius;
	return *this;
}

rb::CircleCollider::CircleCollider(CircleCollider&& rhs)
	: radius(rhs.radius)
{}
CircleCollider& rb::CircleCollider::operator=(CircleCollider&& rhs)
{
	radius = rhs.radius;
	return *this;
}

float rb::CircleCollider::GetRadius() const
{
	return radius;
}

void rb::CircleCollider::SetRadius(float val)
{
	radius = val;
}

std::unique_ptr<Collider> rb::CircleCollider::Clone() const
{
	return std::make_unique<CircleCollider>(*this);
}
