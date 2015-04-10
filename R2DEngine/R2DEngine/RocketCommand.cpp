#include "RocketCommand.h"
#include <functional>
#include "RDebug.h"
#include "GameObject.h"

using namespace std::placeholders;

rb::RocketCommand::RocketCommand()
{
	LoadResources();

	testScene = std::make_shared<R2DScene>(CreateNewScene());
	missilePrefab = std::make_unique<GameObject>(TextureManager::GetTexture("Missile"));
	missilePrefab->SetTransform(Vec2(500.0f), glm::radians(30.0f));
	missilePrefab->GetTransform()->size *= 0.2f;

	Input::RegisterKeyCallback(std::bind(&RocketCommand::OnKeyboard, this, _1, _2));
	Input::RegisterMouseClickCallback(std::bind(&RocketCommand::OnMouseClick, this, _1, _2, _3));

	testScene->Instantiate(*missilePrefab);
	testScene->Instantiate(*missilePrefab, Vec2(200.0f), glm::radians(90.0f));
	testScene->Instantiate(*missilePrefab, Vec2(900.0f, 500.0f), 0.0f);
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
		//missilePrefab->rigidbody->velocity = Vec2(0.0f, 100.0f);
		auto missileClone = testScene->Instantiate(*missilePrefab, Screen::ToWorldCoords(mousePosition), 0.0f);
		//Debug::Log("missile rb copies " + ToString(missileClone->rigidbody.use_count()));
		missileClone->GetRigidbody()->velocity = Vec2(0.0f, 100.0f);
	}
}

void rb::RocketCommand::LoadResources()
{
	TextureManager::LoadTexture("Missile", "Missile.png");
	TextureManager::LoadTexture("Asteroid", "asteroid.png");
}


