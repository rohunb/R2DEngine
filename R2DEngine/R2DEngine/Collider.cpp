#include "Collider.h"
#include "RDebug.h"

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
void rb::Collider::RegisterCollisionCallback(const CollisionCallback& _OnCollision)
{
	assert(_OnCollision);
	this->OnCollision = _OnCollision;
}

void rb::Collider::OnCollisionEnter(const Collider& otherCol)
{
	//Debug::Log("collision enter");
	if (OnCollision) OnCollision(otherCol);
}



