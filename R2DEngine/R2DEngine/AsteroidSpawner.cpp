#include "AsteroidSpawner.h"
#include "RDebug.h"
#include "TextureManager.h"
#include "Screen.h"
#include "RTime.h"
#include "RRandom.h"

void rb::AsteroidSpawner::Start()
{
	Debug::Log("Asteroid spawner start");

	currentTime = 0.0f;
	spawnInterval = 1.0f;
	spawnPos = Vec2(0.0f);
	asteroidSpeed = 200.0f;
	asteroidPrefab = std::make_unique<GameObject>(TextureManager::GetTexture("Asteroid"));
	asteroidPrefab->GetTransform()->size *= 0.3f;
}

void rb::AsteroidSpawner::Update(float dt)
{
	//Debug::Log("Asteroid spawner update");
	if (currentTime >= spawnInterval)
	{
		//spawnPos = Random::UnitVector() * Random::RangeFromZero(Screen::HeightToFloat()*0.5f) + Screen::Center();
		float xPos = Random::Range(0.0f, Screen::WidthToFloat());
		float yPos = Screen::HeightToFloat();
		spawnPos = Vec2(xPos, yPos);
		auto asteroidClone = Instantiate(*asteroidPrefab, spawnPos, 0.0f);
		asteroidClone->GetRigidbody()->velocity = RVector2::down * asteroidSpeed;
		currentTime = 0.0f;
	}
	currentTime += RTime::DeltaTime();
}