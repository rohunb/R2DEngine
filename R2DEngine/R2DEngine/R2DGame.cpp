#include "R2DGame.h"
#include <functional>
#include <assert.h>
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
	LoadDefaultResources();
}

void rb::R2DGame::StartGame()
{
	/*missile = std::make_shared<GameObject>(TextureManager::GetTexture("Missile"));
	missile->Init();
	engine->GetRenderEngine().AddNewRenderer(missile->GetRenderer());
	missile->GetTransform().size *= 0.2f;
	missile->GetTransform().position = Vec2(500.0f);
	missile->GetTransform().rotation = glm::radians(30.0f);

	asteroid = std::make_shared<GameObject>(TextureManager::GetTexture("Asteroid"));
	asteroid->Init();
	engine->GetRenderEngine().AddNewRenderer(asteroid->GetRenderer());
	asteroid->GetTransform().position = Vec2(200.0f);
	asteroid->GetTransform().size *= 0.5f;*/

	Input::RegisterKeyCallback(std::bind(&R2DGame::OnKeyboard, this, _1, _2));
	engine->Run(std::bind(&R2DGame::Update, this, _1));
}

void rb::R2DGame::Update(float dt)
{
	//Debug::Log("Game Update " + ToString(dt));
}

rb::R2DScene rb::R2DGame::CreateNewScene()
{
	std::shared_ptr<R2DScene> newScene = std::make_shared<R2DScene>(std::bind(&R2DGame::RegisterNewGameObject, this, _1));
	sceneList.push_back(newScene);
	return *newScene;
}

void rb::R2DGame::RegisterNewGameObject(GameObject& gameObject)
{
	Debug::Log("Register new go");
	assert(&gameObject && "GameObject is null");
	gameObject.Init();
	engine->GetRenderEngine().AddNewRenderer(gameObject.GetRenderer());
	//register with other engines if required
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

