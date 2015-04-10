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
{}

rb::GameObject::GameObject(const Texture& texture)
	:transform(std::make_shared<Transform>()),
	renderer(std::make_shared<SpriteRenderer>(texture))
{
	transform->size = Vec2(renderer->GetTexture().width, renderer->GetTexture().height);
}

rb::GameObject::GameObject(const GameObject& rhs)
	:transform(std::shared_ptr<Transform>(new Transform(*rhs.transform))),
	renderer(rhs.renderer)
{}

rb::GameObject::GameObject(GameObject&& rhs)
	:transform(std::move(rhs.transform)),
	renderer(std::move(rhs.renderer))
{}
GameObject& rb::GameObject::operator=(const GameObject& rhs)
{
	transform = std::shared_ptr<Transform>(new Transform(*rhs.transform));
	renderer = rhs.renderer;
	return *this;
}
GameObject& rb::GameObject::operator=(GameObject&& rhs)
{
	transform = std::move(rhs.transform);
	renderer = std::move(rhs.renderer);
	return *this;
}
rb::GameObject::~GameObject()
{

}
void rb::GameObject::SetTransform(const Vec2& position, float rotation)
{
	SetTransform(position, rotation, transform->size);
}

void rb::GameObject::SetTransform(const Vec2& position, float rotation, const Vec2& size)
{
	transform->position = position;
	transform->rotation = rotation;
	transform->size = size;
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