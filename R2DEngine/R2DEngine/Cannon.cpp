#include "Cannon.h"
#include "TextureManager.h"
#include "Screen.h"
#include "RDebug.h"
#include "TimedDestroy.h"
#include "TimedAction.h"
#include "CircleCollider.h"

using namespace rb;

void rb::Cannon::Start()
{
	//Debug::Log("Cannon start");
	missileSpeed = 500.0f;
	missilePrefab = std::make_unique<GameObject>(TextureManager::GetTexture("Missile"));
	missilePrefab->GetTransform()->size *= 0.1f;
	missilePrefab->AddComponent<Rigidbody2D>();
	missilePrefab->AddScript<TimedDestroy>();
	missilePrefab->AddScript<TimedAction>();

	auto& explodeTex = TextureManager::GetTexture("Explosion");
	explosionPrefab = std::make_unique<GameObject>(explodeTex);
	explosionPrefab->tag = "Explosion";
	explosionPrefab->GetTransform()->size = Vec2(80.0f);
	auto& anim = explosionPrefab->AddComponent<SpriteAnimator>();
	anim->Initialize(8, 3, 20, 0.01f, false);
	//anim->Initialize(8, 8, 64, 0.01f, false);
	explosionPrefab->AddScript<TimedDestroy>();
	auto& col = explosionPrefab->AddComponent<CircleCollider>();
	col->SetRadius(explosionPrefab->GetTransform()->size.x*0.5f);

	onMouseClick = Input::RegisterMouseClickCallback(
		[&](int button, int action, const Vec2& mousePos){OnMouseClick(button, action, mousePos); });
	onKeyboard = Input::RegisterKeyCallback([&](int key, int action){OnKeyboard(key, action); });
}

void rb::Cannon::Update(float dt)
{
	//Debug::Log("cannon update");
}
void Cannon::Fire(const Vec2& targetPos)
{
	//const auto& missileClone = Instantiate(*missilePrefab, Screen::ToWorldCoords(mousePosition), 0.0f);

	const Vec2 dir = targetPos - gameObject->GetTransform()->position;
	const float distToTarget = glm::length(dir);
	auto& missileClone = Instantiate(*missilePrefab, gameObject->GetTransform()->position, 0.0f);
	missileClone->GetRigidbody()->velocity = dir / distToTarget * missileSpeed;
	missileClone->GetTransform()->LookAt(targetPos);
	const float timeToTarget = distToTarget / missileSpeed;
	assert(missileClone->GetScript<TimedAction>());
	missileClone->GetScript<TimedAction>()->SetTimedAction(
		[=]()
	{
		auto& explosionClone = Instantiate(*explosionPrefab, targetPos, 0.0f);
		pos = targetPos;
		auto& collider = explosionClone->GetCollider();
		assert(collider);
		collider->RegisterCollisionCallback([this](Collider& other){OnCollision(other); });
		assert(explosionClone->GetScript<TimedDestroy>());
		explosionClone->GetScript<TimedDestroy>()->StartDestroyTimer(1.0f);
	}, timeToTarget);
	assert(missileClone->GetScript<TimedDestroy>());
	missileClone->GetScript<TimedDestroy>()->StartDestroyTimer(timeToTarget);
}

void rb::Cannon::OnMouseClick(int button, int action, const Vec2& mousePosition)
{
	if (action == GLFW_PRESS)
	{
		Fire(Screen::ToWorldCoords(mousePosition));
	}
}

void rb::Cannon::OnKeyboard(int key, int action)
{
	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
	{
		Fire(Screen::ToWorldCoords(Input::GetMousePosition()));
	}
}

void rb::Cannon::OnCollision(Collider& other)
{
	assert(other.GetGameObject());
	if (other.GetGameObject()->tag == "Asteroid")
	{
		//Debug::Log("Collided with " + otherGO->tag + "dist " + ToString(glm::distance(pos, other.GetGameObject()->GetTransform()->position)));
		other.GetGameObject()->GetRenderer()->SetColour(Colour::red);
		Destroy(other.GetGameObject());
	}
}

void rb::Cannon::OnDestroy()
{
	//Debug::Log("Cannon on destroy");
	Input::RemoveKeyCallback(onKeyboard);
	Input::RemoveMouseClickCallback(onMouseClick);
}

std::unique_ptr<R2DScript> Cannon::Clone() const
{
	return std::make_unique<Cannon>();
}
