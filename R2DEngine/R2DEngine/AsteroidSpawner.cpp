#include "AsteroidSpawner.h"
#include "RDebug.h"
#include "TextureManager.h"
#include "Screen.h"
#include "RTime.h"
#include "RRandom.h"
#include "Cannon.h"

using namespace rb;

void rb::AsteroidSpawner::Start()
{
	Debug::Log("Asteroid spawner start");

	currentTime = 0.0f;
	spawnInterval = 0.5f;
	asteroidVelY = 200.0f;
	asteroidVelXRange = 200.0f;
	asteroidPrefab = std::make_unique<GameObject>(TextureManager::GetTexture("Asteroid"));
	asteroidPrefab->GetTransform()->size *= 0.3f;
	asteroidPrefab->AddComponent<Rigidbody2D>();
	//asteroidPrefab->AddComponent<Cannon>();
}

void rb::AsteroidSpawner::Update(float dt)
{
	//Debug::Log("Asteroid spawner update");

	if (currentTime >= spawnInterval)
	{
		/*if (counter <= 4000)
		{
			for (size_t i = 0; i < 1000; i++)
			{
				spawnPos = Random::UnitVector() * Random::RangeFromZero(Screen::HeightToFloat()*0.5f) + Screen::Center();
				auto asteroidClone = Instantiate(*asteroidPrefab, spawnPos, 0.0f);
				counter++;
			}
		}*/
		
		const float xPos = Random::Range(0.0f, Screen::WidthToFloat());
		const float yPos = Screen::HeightToFloat();
		const Vec2 spawnPos = Vec2(xPos, yPos);
		const auto& asteroidClone = Instantiate(*asteroidPrefab, spawnPos, 0.0f);
		const Vec2 velocity = Vec2(Random::Range(-asteroidVelXRange, asteroidVelXRange), -asteroidVelY);
		asteroidClone->GetRigidbody()->velocity = velocity;
		currentTime = 0.0f;
	}
	currentTime += dt;
}

void rb::AsteroidSpawner::OnDestroy()
{

}

std::unique_ptr<R2DScript> rb::AsteroidSpawner::Clone() const
{
	return std::make_unique<AsteroidSpawner>();
}
