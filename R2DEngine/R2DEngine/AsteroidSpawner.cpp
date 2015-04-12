#include "AsteroidSpawner.h"

void rb::AsteroidSpawner::Start()
{
	Debug::Log("Asteroid spawner start");

	currentTime = 0.0f;
	spawnInterval = 0.3f;
	startPos = Vec2(0.0f);
	asteroidPrefab = std::make_unique<GameObject>(TextureManager::GetTexture("Asteroid"));
	//asteroidPrefab->SetTransform(Vec2(200.0f), 0.0f);
	asteroidPrefab->GetTransform()->size *= 0.3f;
	//Instantiate(*asteroidPrefab);
}

void rb::AsteroidSpawner::Update(float dt)
{
	//Debug::Log("Asteroid spawner update");
	if (currentTime >= spawnInterval)
	{
		Instantiate(*asteroidPrefab, startPos, 0.0f);
		startPos += Vec2(15.0f);
		currentTime = 0.0f;
	}
	currentTime += RTime::DeltaTime();
}
