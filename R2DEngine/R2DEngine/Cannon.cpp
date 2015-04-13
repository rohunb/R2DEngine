#include "Cannon.h"
#include "TextureManager.h"
#include "Screen.h"
#include "RDebug.h"
#include "TimedDestroy.h"

using namespace rb;

void rb::Cannon::Start()
{
	//Debug::Log("Cannon start");
	missileSpeed = 500.0f;
	missilePrefab = std::make_unique<GameObject>(TextureManager::GetTexture("Missile"));
	missilePrefab->GetTransform()->size *= 0.1f;
	missilePrefab->AddScript<TimedDestroy>();

	onMouseClick = Input::RegisterMouseClickCallback([&](int button, int action, const Vec2& mousePos){OnMouseClick(button, action, mousePos); });
	onKeyboard = Input::RegisterKeyCallback([&](int key, int action){OnKeyboard(key, action); });
}

void rb::Cannon::Update(float dt)
{
	//Debug::Log("cannon update");
}
void Cannon::Fire(const Vec2& targetPos)
{
	//auto missileClone = Instantiate(*missilePrefab, Screen::ToWorldCoords(mousePosition), 0.0f);

	Vec2 dir = targetPos - gameObject->GetTransform()->position;
	float distToTarget = glm::length(dir);
	auto missileClone = Instantiate(*missilePrefab, gameObject->GetTransform()->position, 0.0f);
	missileClone->GetRigidbody()->velocity = dir / distToTarget * missileSpeed;
	missileClone->GetTransform()->LookAt(targetPos);
	float timeToTarget = distToTarget / missileSpeed;
	missileClone->GetScript<TimedDestroy>()->StartDestroyTimer(timeToTarget);
	//Debug::Log("Dist: " + ToString(distToTarget) + " Time: " + ToString(timeToTarget));

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

void rb::Cannon::OnDestroy()
{
	Input::RemoveMouseClickCallback(onMouseClick);
	Input::RemoveKeyCallback(onKeyboard);
}
