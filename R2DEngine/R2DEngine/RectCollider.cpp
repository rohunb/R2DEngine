#include "RectCollider.h"

using namespace rb;


std::unique_ptr<Collider> rb::RectCollider::Clone() const
{
	return std::make_unique<RectCollider>(*this);
}
