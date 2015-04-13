#include "GameObject.h"
#include "Texture.h"
#include "RDebug.h"
#include "R2DScript.h"

using namespace rb;

void rb::GameObject::Init()
{
	//Debug::Log("GameObject init");
	transform->gameObject = shared_from_this();
	if(renderer) renderer->gameObject = shared_from_this();
	if(rigidbody) rigidbody->gameObject = shared_from_this();
	for (auto& script : scripts)
	{
		script->gameObject = shared_from_this();
		script->Start();
	}
}

rb::GameObject::GameObject()
	:transform(std::make_shared<Transform>())
{}

rb::GameObject::GameObject(const Texture& texture)
	:transform(std::make_shared<Transform>()),
	renderer(std::make_shared<SpriteRenderer>(texture)),
	rigidbody(std::make_shared<Rigidbody2D>())
{
	transform->size = Vec2(renderer->GetTexture().width, renderer->GetTexture().height);
}

rb::GameObject::GameObject(GameObject&& rhs)
	: transform(std::move(rhs.transform)),
	scripts(std::move(rhs.scripts))
{
	if (rhs.renderer)
	{
		renderer=std::move(rhs.renderer);
	}
	if (rhs.rigidbody)
	{
		rigidbody=std::move(rhs.rigidbody);
	}
}
rb::GameObject::GameObject(const GameObject& rhs)
	:transform(std::make_shared<Transform>(*(rhs.transform)))
{
	if (rhs.renderer)
	{
		renderer = std::make_shared<SpriteRenderer>(*(rhs.renderer));
	}
	if (rhs.rigidbody)
	{
		rigidbody = std::make_shared<Rigidbody2D>(*(rhs.rigidbody));
	}
	scripts.reserve(rhs.scripts.size());
	for (auto& rhsScript: rhs.scripts)
	{
		scripts.push_back(rhsScript->Clone());
	}
}

GameObject& rb::GameObject::operator=(const GameObject& rhs)
{
	transform = std::make_shared<Transform>(*(rhs.transform));
	if (rhs.renderer)
	{
		renderer = std::make_shared<SpriteRenderer>(*(rhs.renderer));
	}
	if (rhs.rigidbody)
	{
		rigidbody = std::make_shared<Rigidbody2D>(*(rhs.rigidbody));
	}
	scripts = rhs.scripts;
	return *this;
}
GameObject& rb::GameObject::operator=(GameObject&& rhs)
{
	transform = std::move(rhs.transform);
	if (rhs.renderer)
	{
		renderer = std::move(rhs.renderer);
	}
	if (rhs.rigidbody)
	{
		rigidbody = std::move(rhs.rigidbody);
	}
	scripts = std::move(rhs.scripts);
	return *this;
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

std::shared_ptr<Transform> rb::GameObject::GetTransform() const
{
	return transform;
}
std::shared_ptr<SpriteRenderer> rb::GameObject::GetRenderer() const
{
	return renderer;
}
std::shared_ptr<Rigidbody2D> rb::GameObject::GetRigidbody() const
{
	return rigidbody;
}
std::vector<std::shared_ptr<class R2DScript>> rb::GameObject::GetScripts() const
{
	return scripts;
}
