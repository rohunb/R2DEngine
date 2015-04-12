#include "GameScene.h"
#include "AsteroidSpawner.h"

void rb::GameScene::Start()
{
	/*asteroidPrefab = std::make_unique<GameObject>(TextureManager::GetTexture("Asteroid"));
	asteroidPrefab->SetTransform(Vec2(200.0f),0.0f);
	asteroidPrefab->GetTransform()->size *= 0.3f;

	Instantiate(*asteroidPrefab);
	Instantiate(*asteroidPrefab, Vec2(500.0f), 0.0f);*/

	BackgroundColour(Colour::darkGrey);
	asteroidSpawner = std::make_unique<GameObject>();
	asteroidSpawner->AddScript<AsteroidSpawner>();
	
	Instantiate(*asteroidSpawner);

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
