#include "R2DGame.h"
#include <functional>
#include <assert.h>
#include "RDebug.h"
#include "FileManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "R2DScript.h"

using namespace rb;
using namespace std::placeholders;

rb::R2DGame::R2DGame()
{
	engine = std::make_unique<R2DEngine>();
	LoadDefaultResources();
}

void rb::R2DGame::StartGame()
{
	Input::RegisterKeyCallback(std::bind(&R2DGame::OnKeyboard, this, _1, _2));
	engine->Run(std::bind(&R2DGame::Update, this, _1));
}

void rb::R2DGame::Update(float dt)
{
	//Debug::Log("Game Update " + ToString(dt));
	currentScene->Update(dt);
	currentScene->RemoveDestroyedObjects();
}

void rb::R2DGame::LoadScene(std::shared_ptr<R2DScene> scene)
{
	if (currentScene.get())
	{
		currentScene->DestroyAllObjects();
		currentScene->Exit();
	}
	else
	{
		Debug::Log("Current scene is null");
	}
	currentScene = scene;
	scene->Start();
}

void rb::R2DGame::RegisterNewGameObject(GameObject& gameObject)
{
	//Debug::Log("Register new go");
	assert(&gameObject && "GameObject is null");
	for (auto& script : gameObject.GetScripts())
	{
		script->currentScene = currentScene;
		Debug::Log("Add Script: script ref count: " + ToString(script.use_count()));
	}
	gameObject.Init();
	if (gameObject.GetRenderer())
	{
		engine->GetRenderEngine()->AddNewRenderer(gameObject.GetRenderer());
	}
	if (gameObject.GetRigidbody())
	{
		engine->GetPhysicsEngine()->AddNewRigidbody(gameObject.GetRigidbody());
	}
}

void rb::R2DGame::DestroyGameObject(std::shared_ptr<GameObject>& gameObject)
{
	//Debug::Log("Destroying GameObject");
	assert(gameObject.get() && "GameObject pointer is null");
	for (auto& script : gameObject->GetScripts())
	{
		script->OnDestroy();
	}
	if (gameObject->GetRenderer())
	{
		engine->GetRenderEngine()->RemoveRenderer(gameObject->GetRenderer());
	}
	if (gameObject->GetRigidbody())
	{
		engine->GetPhysicsEngine()->RemoveRigidbody(gameObject->GetRigidbody());
	}
}

void rb::R2DGame::OnKeyboard(int key, int action)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		engine->ShutDown();
	}
}
void rb::R2DGame::LoadDefaultResources()
{
	ShaderManager::LoadShader("SpriteShader.vert", "SpriteShader.frag", Shader::ShaderType::SpriteShader);
	ShaderManager::LoadShader("PointSprite.vert", "PointSprite.frag", "PointSprite.geom", Shader::ShaderType::PointSprite);
	
}

