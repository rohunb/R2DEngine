#include "RocketCommand.h"
#include "RDebug.h"
#include "GameObject.h"

rb::RocketCommand::RocketCommand()
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
	asteroid->GetTransform().size *= 0.5f; */


	testScene = std::make_shared<R2DScene>(CreateNewScene());
	missilePrefab = std::make_unique<GameObject>(TextureManager::GetTexture("Missile"));
	missilePrefab->GetTransform().size *= 0.2f;
	missilePrefab->GetTransform().position = Vec2(500.0f);
	missilePrefab->GetTransform().rotation = glm::radians(30.0f);

	testScene->Instantiate(*missilePrefab);
	testScene->Instantiate(*missilePrefab, Vec2(200.0f), 90.0f);
}

void rb::RocketCommand::StartGame()
{
	R2DGame::StartGame();
}


