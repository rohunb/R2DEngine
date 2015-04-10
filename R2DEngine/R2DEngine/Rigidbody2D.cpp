#include "Rigidbody2D.h"
#include "GameObject.h"

rb::Rigidbody2D::Rigidbody2D()
	:Rigidbody2D(Vec2(0.0f))
{}
rb::Rigidbody2D::Rigidbody2D(const Vec2& velocity)
	: velocity(velocity)
{}
void rb::Rigidbody2D::Update(float dt)
{
	gameObject->GetTransform()->position += velocity * dt;
}
