#include "RectCollider.h"

using namespace rb;


void rb::RectCollider::Init()
{
	
}
std::unique_ptr<Collider> rb::RectCollider::Clone() const
{
	return std::make_unique<RectCollider>(*this);
}
