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
		std::unique_ptr<class GameObject> asteroidPrefab;
		float spawnInterval;
		float currentTime;
		Vec2 asteroidSpeed;
		Vec2 spawnPos;
	};
}

#endif // R_ASTEROID_SPAWNER_H_
