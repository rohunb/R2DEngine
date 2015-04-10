#include "RocketCommand.h"
#include "RDebug.h"
#include "GameObject.h"

rb::RocketCommand::RocketCommand()
{

	testScene = std::make_shared<R2DScene>(CreateNewScene());
	missilePrefab = std::make_unique<GameObject>(TextureManager::GetTexture("Missile"));
	missilePrefab->SetTransform(Vec2(500.0f), glm::radians(30.0f));
	missilePrefab->GetTransform().size *= 0.2f;

	testScene->Instantiate(*missilePrefab);
	testScene->Instantiate(*missilePrefab, Vec2(200.0f), glm::radians(90.0f));
	testScene->Instantiate(*missilePrefab, Vec2(900.0f, 500.0f), 0.0f);
}

void rb::RocketCommand::StartGame()
{
	R2DGame::StartGame();
}


