#include "GameScene.h"
#include "AsteroidSpawner.h"
#include "Cannon.h"

void rb::GameScene::Start()
{
	BackgroundColour(Colour::darkGrey);

	asteroidSpawnerPrefab = std::make_unique<GameObject>();
	asteroidSpawnerPrefab->AddScript<AsteroidSpawner>();
	Instantiate(*asteroidSpawnerPrefab);

	cannonPrefab = std::make_unique<GameObject>();
	cannonPrefab->AddScript<Cannon>();
	cannonPrefab->SetTransform(Vec2(Screen::WidthToFloat()*0.5f, 50.0f));
	Instantiate(*cannonPrefab);

	mouseClickEvent = Input::RegisterMouseClickCallback([&](int button, int action, const Vec2& mousePos){OnMouseClick(button, action, mousePos); });
}

void rb::GameScene::Update(float dt)
{
	R2DScene::Update(dt);
}

void rb::GameScene::OnMouseClick(int button, int action, const Vec2& mousePos)
{
	/*if (action == GLFW_PRESS)
		Instantiate(*asteroidPrefab, Screen::ToWorldCoords(mousePos), 0.0f);*/
}

void rb::GameScene::Exit()
{
	Input::RemoveMouseClickCallback(mouseClickEvent);
}
