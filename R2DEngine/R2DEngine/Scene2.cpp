#include "Scene2.h"

void rb::Scene2::Start()
{
	BackgroundColour(Colour::red);

	missilePrefab = std::make_unique<GameObject>(TextureManager::GetTexture("Missile"));
	missilePrefab->SetTransform(Vec2(200.0f), glm::radians(30.0f));
	missilePrefab->GetTransform()->size *= 0.1f;

	Instantiate(*missilePrefab);
}

void rb::Scene2::Update(float dt)
{

}

void rb::Scene2::Exit()
{

}
