#include "Cannon.h"
#include "TextureManager.h"
#include "RInput.h"
#include "Screen.h"

void rb::Cannon::Start()
{
	//Debug::Log("Cannon start");
	missileSpeed = 500.0f;
	missilePrefab = std::make_unique<GameObject>(TextureManager::GetTexture("Missile"));
	missilePrefab->GetTransform()->size *= 0.1f;

	Input::RegisterMouseClickCallback([&](int button, int action, const Vec2& mousePos){OnMouseClick(button, action, mousePos); });
}

void rb::Cannon::Update(float dt)
{
	//Debug::Log("cannon update");
}

void rb::Cannon::OnMouseClick(int button, int action, const Vec2& mousePosition)
{
	//auto missileClone = Instantiate(*missilePrefab, Screen::ToWorldCoords(mousePosition), 0.0f);

	if (action == GLFW_PRESS)
	{
		Vec2 targetPos = Screen::ToWorldCoords(mousePosition);
		Vec2 dir = glm::normalize(targetPos - gameObject->GetTransform()->position);
		auto missileClone = Instantiate(*missilePrefab, gameObject->GetTransform()->position, 0.0f);
		missileClone->GetRigidbody()->velocity = dir*missileSpeed;
		missileClone->GetTransform()->LookAt(targetPos);
	}
}
