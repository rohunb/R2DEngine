#include "R2DGame.h"
#include <functional>
#include "RDebug.h"
#include "FileManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "GameObject.h"


using namespace rb;
using namespace std::placeholders;

rb::R2DGame::R2DGame()
{
	engine = std::make_unique<R2DEngine>();
}

void rb::R2DGame::StartGame()
{
	LoadDefaultResources();

	missile = std::make_shared<GameObject>(TextureManager::GetTexture("Missile"));
	missile->Init();
	missile->GetTransform().size *= 0.2f;
	missile->GetTransform().position = Vec2(500.0f);
	missile->GetTransform().rotation = glm::radians(30.0f);

	asteroid = std::make_shared<GameObject>(TextureManager::GetTexture("Asteroid"));
	asteroid->Init();
	asteroid->GetTransform().position = Vec2(200.0f);
	asteroid->GetTransform().size *= 0.5f;

	Input::RegisterKeyCallback(std::bind(&R2DGame::OnKeyboard, this, _1, _2));
	engine->Run(std::bind(&R2DGame::Update, this, _1),
		std::bind(&R2DGame::Render, this));
}

void rb::R2DGame::Render()
{
	//Debug::Log("Game Render");
	missile->GetRenderer().Render();
	asteroid->GetRenderer().Render();
}

void rb::R2DGame::Update(float dt)
{
	//Debug::Log("Game Update " + ToString(dt));
}

rb::R2DScene rb::R2DGame::CreateNewScene()
{
	std::shared_ptr<R2DScene> newScene = std::make_shared<R2DScene>();
	sceneList.push_back(newScene);
	return *newScene;
}

void rb::R2DGame::OnKeyboard(int key, int action)
{
	Debug::Log("OnKeyboard: key " + ToString(key) + " action " + ToString(action));
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		engine->ShutDown();
	}
}
void rb::R2DGame::LoadDefaultResources()
{
	ShaderManager::LoadShader("SpriteShader.vert", "SpriteShader.frag", Shader::ShaderType::SpriteShader);
	TextureManager::LoadTexture("Missile", "Missile.png");
	TextureManager::LoadTexture("Asteroid", "asteroid.png");
	
}
