#include "GameObject.h"
#include "Texture.h"
#include "RDebug.h"
#include "R2DScript.h"
#include "CircleCollider.h"
#include "RectCollider.h"

using namespace rb;

void rb::GameObject::Init()
{
	//Debug::Log("GameObject init");
	transform->gameObject = shared_from_this();
	if (renderer) renderer->gameObject = shared_from_this();
	if (rigidbody) rigidbody->gameObject = shared_from_this();
	if (animator) animator->gameObject = shared_from_this();
	if (collider) collider->gameObject = shared_from_this();

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
	: transform(std::make_shared<Transform>()),
	renderer(std::make_shared<SpriteRenderer>(texture))
{
	transform->size = Vec2(renderer->GetTexture().width, renderer->GetTexture().height);
}

rb::GameObject::GameObject(const GameObject& rhs)
	:tag(rhs.tag),
	name(rhs.name),
	destroyed(rhs.destroyed),
	transform(std::make_shared<Transform>(*(rhs.transform)))
{
	if (rhs.renderer) renderer = std::make_shared<SpriteRenderer>(*(rhs.renderer));
	if (rhs.animator) animator = std::make_shared<SpriteAnimator>(*(rhs.animator));
	if (rhs.rigidbody) rigidbody = std::make_shared<Rigidbody2D>(*(rhs.rigidbody));
	if (rhs.collider) collider = rhs.collider->Clone();

	scripts.reserve(rhs.scripts.size());
	for (auto& rhsScript : rhs.scripts)
	{
		scripts.push_back(rhsScript->Clone());
	}
}

GameObject& rb::GameObject::operator=(const GameObject& rhs)
{
	tag = rhs.tag;
	name = rhs.name;
	destroyed = rhs.destroyed;
	transform = std::make_shared<Transform>(*(rhs.transform));
	if (rhs.renderer) renderer = std::make_shared<SpriteRenderer>(*(rhs.renderer));
	if (rhs.animator) animator = std::make_shared<SpriteAnimator>(*(rhs.animator));
	if (rhs.rigidbody) rigidbody = std::make_shared<Rigidbody2D>(*(rhs.rigidbody));
	if (rhs.collider) collider = rhs.collider->Clone();
	scripts.reserve(rhs.scripts.size());
	for (auto& rhsScript : rhs.scripts)
	{
		scripts.push_back(rhsScript->Clone());
	}
	return *this;
}

rb::GameObject::GameObject(GameObject&& rhs)
	: tag(std::move(rhs.tag)),
	name(std::move(rhs.name)),
	destroyed(rhs.destroyed),
	transform(std::move(rhs.transform)),
	scripts(std::move(rhs.scripts))
{
	if (rhs.renderer) renderer = std::move(rhs.renderer);
	if (rhs.animator) animator = std::move(rhs.animator);
	if (rhs.rigidbody) rigidbody = std::move(rhs.rigidbody);
	if (rhs.collider) collider = std::move(rhs.collider);
}
GameObject& rb::GameObject::operator=(GameObject&& rhs)
{
	tag = std::move(rhs.tag);
	name = std::move(rhs.name);
	destroyed = rhs.destroyed;
	transform = std::move(rhs.transform);
	if (rhs.renderer) renderer = std::move(rhs.renderer);
	if (rhs.animator) animator = std::move(rhs.animator);
	if (rhs.rigidbody) rigidbody = std::move(rhs.rigidbody);
	if (rhs.collider) collider = std::move(rhs.collider);
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
std::shared_ptr<SpriteAnimator> rb::GameObject::GetAnimator() const
{
	return animator;
}
std::vector<std::shared_ptr<R2DScript>> rb::GameObject::GetScripts() const
{
	return scripts;
}

std::shared_ptr<Collider> rb::GameObject::GetCollider() const
{
	return collider;
}

template<>
std::shared_ptr<Rigidbody2D> GameObject::AddComponent()
{
	assert(!rigidbody && "Rigidbody already attached");
	rigidbody = std::make_shared<Rigidbody2D>();
	return rigidbody;
}
template<>
std::shared_ptr<Rigidbody2D> GameObject::GetComponent()
{
	return rigidbody;
}
template<>
std::shared_ptr<Transform> GameObject::AddComponent()
{
	assert(!transform && "Transform already attached");
	transform = std::make_shared<Transform>();
	return transform;
}
template<>
std::shared_ptr<Transform> GameObject::GetComponent()
{
	return transform;
}
template<>
std::shared_ptr<SpriteRenderer> GameObject::AddComponent()
{
	assert(!renderer && "Sprite Renderer already attached");
	renderer = std::make_shared<SpriteRenderer>();
	return renderer;
}
template<>
std::shared_ptr<SpriteRenderer> GameObject::GetComponent()
{
	return renderer;
}
template<>
std::shared_ptr<SpriteAnimator> GameObject::AddComponent()
{
	assert(!animator && "Animator already attached");
	animator = std::make_shared<SpriteAnimator>();
	return animator;
}
template<>
std::shared_ptr<SpriteAnimator> GameObject::GetComponent()
{
	return animator;
}
template<>
std::shared_ptr<CircleCollider> GameObject::AddComponent()
{
	assert(!collider && "Collidor already attached");
	collider = std::make_shared<CircleCollider>();
	return std::dynamic_pointer_cast<CircleCollider>(collider);
}
template<>
std::shared_ptr<CircleCollider> GameObject::GetComponent()
{
	return std::dynamic_pointer_cast<CircleCollider>(collider);
}
template<class T>
std::shared_ptr<T> AddComponent()
{
	assert("Must be a built-in component such as Rigidbody2D")
}
template<class T>
std::shared_ptr<T> GetComponent()
{
	assert("Must be a built-in component such as Rigidbody2D")
}



