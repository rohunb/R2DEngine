#include "Collider.h"

using namespace rb;

rb::Collider::Collider(Collider&& rhs)
{
	*this = rhs;
}

Collider::ColliderType rb::Collider::GetType() const
{
	return type;
}

Collider& rb::Collider::operator=(Collider&& rhs)
{
	*this = rhs;
	return *this;
}

