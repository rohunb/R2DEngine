#include "GameObject.h"
#include "Texture.h"
#include "RDebug.h"

using namespace rb;

void rb::GameObject::Init()
{
	Debug::Log("GameObject init");
	transform->gameObject = shared_from_this();
	renderer->gameObject = shared_from_this();
}


rb::GameObject::GameObject()
{

}

rb::GameObject::GameObject(const Texture& texture)
	:transform(std::make_shared<Transform>()),
	renderer(std::make_shared<SpriteRenderer>(texture))
{
	transform->size = Vec2(renderer->GetTexture().width, renderer->GetTexture().height);
}

rb::GameObject::GameObject(const GameObject& rhs)
	:transform(rhs.transform),
	renderer(rhs.renderer)
{
	/*size_t rhsCompsSize = rhs.components.size();
	components.resize(rhsCompsSize);
	for (size_t i = 0; i < rhsCompsSize; ++i)
	{
		components[i] = rhs.components[i];
	}*/
}

rb::GameObject::GameObject(GameObject&& rhs)
	:transform(std::move(rhs.transform)),
	renderer(std::move(rhs.renderer))
{
	/*size_t rhsCompsSize = rhs.components.size();
	components.resize(rhsCompsSize);
	for (size_t i = 0; i < rhsCompsSize; ++i)
	{
		components[i] = std::move(rhs.components[i]);
	}*/
}
GameObject& rb::GameObject::operator=(const GameObject& rhs)
{
	transform = rhs.transform;
	renderer = rhs.renderer;
	/*size_t rhsCompsSize = rhs.components.size();
	components.resize(rhsCompsSize);
	for (size_t i = 0; i < rhsCompsSize; ++i)
	{
		components[i] = rhs.components[i];
	}*/
	return *this;
}
GameObject& rb::GameObject::operator=(GameObject&& rhs)
{
	transform = std::move(rhs.transform);
	renderer = std::move(rhs.renderer);
	/*size_t rhsCompsSize = rhs.components.size();
	components.resize(rhsCompsSize);
	for (size_t i = 0; i < rhsCompsSize; ++i)
	{
		components[i] = std::move(rhs.components[i]);
	}*/
	return *this;
}
rb::GameObject::~GameObject()
{

}

Transform& rb::GameObject::GetTransform() const
{
	return *transform;
}

SpriteRenderer& rb::GameObject::GetRenderer() const
{
	return *renderer;
}

void rb::GameObject::Destroy()
{

}