#include "RocketCommand.h"
#include <functional>
#include "RDebug.h"
#include "GameObject.h"

using namespace std::placeholders;

rb::RocketCommand::RocketCommand()
{
	LoadResources();

	testScene = std::make_shared<R2DScene>(CreateNewScene());
	//testScene->BackgroundColour(Colour::cyan);
	cannonPos = Vec2(static_cast<float>(Screen::WidthToFloat())*0.5f, 0.0f);
	missilePrefab = std::make_unique<GameObject>(TextureManager::GetTexture("Missile"));
	missilePrefab->SetTransform(cannonPos, glm::radians(0.0f));
	missilePrefab->GetTransform()->size *= 0.1f;
	missileSpeed = 500.0f;

	Input::RegisterKeyCallback(std::bind(&RocketCommand::OnKeyboard, this, _1, _2));
	Input::RegisterMouseClickCallback(std::bind(&RocketCommand::OnMouseClick, this, _1, _2, _3));
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

		missileClone = testScene->Instantiate(*missilePrefab, Screen::ToWorldCoords(mousePosition), 0.0f);

		//Vec2 targetPos = Screen::ToWorldCoords(mousePosition);
		//Vec2 dir = glm::normalize(targetPos - cannonPos);
		//auto missileClone = testScene->Instantiate(*missilePrefab);// , cannonPos, glm::radians(-45.0f));
		//missileClone->GetRigidbody()->velocity = dir*missileSpeed;
		//missileClone->GetTransform()->LookAt(targetPos);
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		testScene->Destroy(missileClone);
	}
}

void rb::RocketCommand::LoadResources()
{
	TextureManager::LoadTexture("Missile", "Missile.png");
	TextureManager::LoadTexture("Asteroid", "asteroid.png");
}


