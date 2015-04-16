#include "Collider.h"

using namespace rb;

rb::Collider::Collider(Collider&& rhs)
{
	*this = rhs;
}


void rb::Collider::Init()
{

}

Collider& rb::Collider::operator=(Collider&& rhs)
{
	*this = rhs;
	return *this;
}

