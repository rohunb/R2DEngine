#include "R2DGame.h"
#include <functional>
#include "RDebug.h"
#include "FileManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

using namespace rb;
using namespace std::placeholders;

rb::R2DGame::R2DGame()
{
	engine = std::make_unique<R2DEngine>();
}

void rb::R2DGame::StartGame()
{
	LoadDefaultResources();

	testObj = std::make_shared<GameObject>(TextureManager::GetTexture("Smiley"));
	testObj->Init();
	testObj->GetTransform().size = Vec2(512.0f);
	testObj->GetTransform().position = Vec2(100.0f);

	Input::RegisterKeyCallback(std::bind(&R2DGame::OnKeyboard, this, _1, _2));
	engine->Run(std::bind(&R2DGame::Update, this, _1),
		std::bind(&R2DGame::Render, this));
}

void rb::R2DGame::Render()
{
	//Debug::Log("Game Render");
	testObj->GetRenderer().Render();
}

void rb::R2DGame::Update(float dt)
{
	//Debug::Log("Game Update " + ToString(dt));
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
	TextureManager::LoadTexture("Smiley", "awesomeface.png");
	
}
