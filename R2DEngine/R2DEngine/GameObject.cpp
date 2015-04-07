#include "GameObject.h"

using namespace rb;

rb::GameObject::GameObject()
{

}
rb::GameObject::GameObject(const GameObject& rhs)
	:transform(rhs.transform)
{
	size_t rhsCompsSize = rhs.components.size();
	components.resize(rhsCompsSize);
	for (size_t i = 0; i < rhsCompsSize; ++i)
	{
		components[i] = rhs.components[i];
	}
}

rb::GameObject::GameObject(GameObject&& rhs)
	:transform(std::move(rhs.transform))
{
	rhs.transform.reset();
	size_t rhsCompsSize = rhs.components.size();
	components.resize(rhsCompsSize);
	for (size_t i = 0; i < rhsCompsSize; ++i)
	{
		components[i] = std::move(rhs.components[i]);
	}
}
GameObject& rb::GameObject::operator=(const GameObject& rhs)
{
	transform = rhs.transform;
	size_t rhsCompsSize = rhs.components.size();
	components.resize(rhsCompsSize);
	for (size_t i = 0; i < rhsCompsSize; ++i)
	{
		components[i] = rhs.components[i];
	}
	return *this;
}
GameObject& rb::GameObject::operator=(GameObject&& rhs)
{
	transform = std::move(rhs.transform);
	rhs.transform.reset();
	size_t rhsCompsSize = rhs.components.size();
	components.resize(rhsCompsSize);
	for (size_t i = 0; i < rhsCompsSize; ++i)
	{
		components[i] = std::move(rhs.components[i]);
	}
	return *this;
}
rb::GameObject::~GameObject()
{

}








void rb::GameObject::Destroy()
{

}