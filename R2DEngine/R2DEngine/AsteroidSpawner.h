#ifndef R_ASTEROID_SPAWNER_H_
#define R_ASTEROID_SPAWNER_H_

#include "R2DScript.h"

namespace rb
{
	class AsteroidSpawner : public R2DScript
	{
	public:
		virtual void Start() override;
		virtual void Update(float dt) override;

	private:
		std::unique_ptr<GameObject> asteroidPrefab;
		float spawnInterval;
		float currentTime;
		float asteroidSpeed;
		Vec2 spawnPos;
		int counter = 0;
	};
}

#endif // R_ASTEROID_SPAWNER_H_
