#include "R2DComponent.h"
#include "GameObject.h"
#include "Transform.h"

using namespace rb;

rb::R2DComponent::R2DComponent()
{}
rb::R2DComponent::R2DComponent(const R2DComponent& rhs)
	:gameObject(rhs.gameObject),
	transform(rhs.transform)
{}
rb::R2DComponent::R2DComponent(R2DComponent&& rhs)
	: gameObject(std::move(rhs.gameObject)),
	transform(std::move(rhs.transform))
{
	rhs.gameObject.reset();
	rhs.transform.reset();
}
R2DComponent& rb::R2DComponent::operator=(const R2DComponent& rhs)
{
	gameObject = rhs.gameObject;
	transform = rhs.transform;
	return *this;
}
R2DComponent& rb::R2DComponent::operator=(R2DComponent&& rhs)
{
	gameObject = std::move(rhs.gameObject);
	transform = std::move(rhs.transform);
	rhs.gameObject.reset();
	rhs.transform.reset();
	return *this;
}

rb::R2DComponent::~R2DComponent()
{

}

GameObject& rb::R2DComponent::GetGameObject() const
{
	return *gameObject.get();
}

Transform& rb::R2DComponent::GetTransform() const
{
	return *transform.get();
}
