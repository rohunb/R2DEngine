#include "R2DComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "RDebug.h"

using namespace rb;

rb::R2DComponent::R2DComponent()
{}

rb::R2DComponent::R2DComponent(const R2DComponent& rhs)
	:gameObject(rhs.gameObject)
{}
rb::R2DComponent::R2DComponent(R2DComponent&& rhs)
	: gameObject(std::move(rhs.gameObject))
{}
R2DComponent& rb::R2DComponent::operator=(const R2DComponent& rhs)
{
	gameObject = rhs.gameObject;
	return *this;
}
R2DComponent& rb::R2DComponent::operator=(R2DComponent&& rhs)
{
	gameObject = std::move(rhs.gameObject);
	return *this;
}

rb::R2DComponent::~R2DComponent()
{

}

GameObject& rb::R2DComponent::GetGameObject() const
{
	auto go = gameObject.lock();
	assert(go && "GameObject reference has expired");
	return *go;
}
