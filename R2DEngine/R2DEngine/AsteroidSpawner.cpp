#include "AsteroidSpawner.h"

void rb::AsteroidSpawner::Start()
{
	Debug::Log("Asteroid spawner start");

	currentTime = 0.0f;
	spawnInterval = 0.1f;
	spawnPos = Vec2(0.0f);
	asteroidPrefab = std::make_unique<GameObject>(TextureManager::GetTexture("Asteroid"));
	asteroidPrefab->GetTransform()->size *= 0.3f;
}

void rb::AsteroidSpawner::Update(float dt)
{
	//Debug::Log("Asteroid spawner update");
	if (currentTime >= spawnInterval)
	{
		spawnPos = Random::UnitVector() * Random::RangeFromZero(Screen::HeightToFloat()*0.5f) + Screen::Center();
		Instantiate(*asteroidPrefab, spawnPos, 0.0f);
		//spawnPos += Vec2(15.0f);
		currentTime = 0.0f;
	}
	currentTime += RTime::DeltaTime();
}
