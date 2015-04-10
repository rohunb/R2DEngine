#include "RocketCommand.h"
#include <functional>
#include "RDebug.h"
#include "GameObject.h"

using namespace std::placeholders;

rb::RocketCommand::RocketCommand()
{
	LoadResources();

	testScene = std::make_shared<R2DScene>(CreateNewScene());
	cannonPos = Vec2(static_cast<float>(Screen::WidthToFloat())*0.5f, 50.0f);
	missilePrefab = std::make_unique<GameObject>(TextureManager::GetTexture("Missile"));
	missilePrefab->SetTransform(cannonPos, glm::radians(0.0f));
	missilePrefab->GetTransform()->size *= 0.2f;
	missileSpeed = 500.0f;

	Input::RegisterKeyCallback(std::bind(&RocketCommand::OnKeyboard, this, _1, _2));
	Input::RegisterMouseClickCallback(std::bind(&RocketCommand::OnMouseClick, this, _1, _2, _3));

	/*testScene->Instantiate(*missilePrefab);
	testScene->Instantiate(*missilePrefab, Vec2(200.0f), glm::radians(90.0f));
	testScene->Instantiate(*missilePrefab, Vec2(900.0f, 500.0f), 0.0f);*/
}

void rb::RocketCommand::StartGame()
{
	R2DGame::StartGame();
}
void rb::RocketCommand::OnKeyboard(int key, int action)
{
	Debug::Log("OnKeyboard: key " + ToString(key) + " action " + ToString(action));
}

void rb::RocketCommand::OnMouseClick(int button, int action, const Vec2& mousePosition)
{
	//Debug::Log("mouse click " + ToString(button) + "," + ToString(action) + ": "+ToString(mousePosition));
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		//auto missileClone = testScene->Instantiate(*missilePrefab, Screen::ToWorldCoords(mousePosition), 0.0f);
		Vec2 dest = Screen::ToWorldCoords(mousePosition);
		Vec2 dir = glm::normalize(dest - cannonPos);
		auto missileClone = testScene->Instantiate(*missilePrefab);//, cannonPos, 0.0f);
		missileClone->GetRigidbody()->velocity = dir*missileSpeed;
	}
}

void rb::RocketCommand::LoadResources()
{
	TextureManager::LoadTexture("Missile", "Missile.png");
	TextureManager::LoadTexture("Asteroid", "asteroid.png");
}


