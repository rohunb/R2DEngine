#include "RocketCommand.h"
#include <functional>
#include "RDebug.h"
#include "GameObject.h"
#include "GameScene.h"
#include "Scene2.h"
#include "TextureManager.h"

using namespace std::placeholders;

rb::RocketCommand::RocketCommand()
{
	LoadResources();

	//Input::RegisterMouseClickCallback([&](int button, int action, const Vec2& mousePosition){OnMouseClick(button, action, mousePosition); });
	Input::RegisterKeyCallback([&](int key, int action){OnKeyboard(key, action); });

	gameScene = CreateNewScene<GameScene>();
	scene2 = CreateNewScene<Scene2>();
	LoadScene(gameScene);
}

void rb::RocketCommand::StartGame()
{
	R2DGame::StartGame();
}
void rb::RocketCommand::OnKeyboard(int key, int action)
{
	Debug::Log("OnKeyboard: key " + ToString(key) + " action " + ToString(action));
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		LoadScene(scene2);
	}
	else if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	{
		LoadScene(gameScene);
	}
}

void rb::RocketCommand::OnMouseClick(int button, int action, const Vec2& mousePosition)
{
	//Debug::Log("mouse click " + ToString(button) + "," + ToString(action) + ": "+ToString(mousePosition));

}

void rb::RocketCommand::LoadResources()
{
	TextureManager::LoadTexture("Missile", "Missile.png");
	TextureManager::LoadTexture("Asteroid", "asteroid.png");
	TextureManager::LoadTexture("Explosion", "explosion.png");

}


