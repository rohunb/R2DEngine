#include "GameScene.h"
#include "AsteroidSpawner.h"
#include "Cannon.h"
#include "Screen.h"
#include "TextureManager.h"

void rb::GameScene::Start()
{
	SetBackgroundColour(Colour::darkGrey);

	asteroidSpawnerPrefab = std::make_unique<GameObject>();
	asteroidSpawnerPrefab->AddScript<AsteroidSpawner>();
	Instantiate(*asteroidSpawnerPrefab);

	cannonPrefab = std::make_unique<GameObject>();
	cannonPrefab->AddScript<Cannon>();
	cannonPrefab->SetTransform(Vec2(Screen::WidthToFloat()*0.5f, 50.0f));
	Instantiate(*cannonPrefab);

	mouseClickEvent = Input::RegisterMouseClickCallback([&](int button, int action, const Vec2& mousePos){OnMouseClick(button, action, mousePos); });

	backgroundPrefab = std::make_unique<GameObject>(TextureManager::GetTexture("Background"));
	backgroundPrefab->SetTransform(Screen::Center(), 0.0f, Screen::GetResolution());
	Instantiate(*backgroundPrefab);

	city1Prefab = std::make_unique<GameObject>(TextureManager::GetTexture("City1"));
	//city1Prefab->GetTransform()->s
	Instantiate(*city1Prefab, Vec2(300.0f, 75.0f),0.0f);
}

void rb::GameScene::Update(float dt)
{
	R2DScene::Update(dt);
}

void rb::GameScene::OnMouseClick(int button, int action, const Vec2& mousePos)
{
	
}

void rb::GameScene::Exit()
{
	Input::RemoveMouseClickCallback(mouseClickEvent);
}
