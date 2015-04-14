#ifndef R_ASTEROID_SPAWNER_H_
#define R_ASTEROID_SPAWNER_H_

#include "R2DScript.h"

namespace rb
{
	class AsteroidSpawner : public R2DScript
	{
	public:
		AsteroidSpawner() = default;
		AsteroidSpawner(const AsteroidSpawner& rhs) = delete;
		AsteroidSpawner& operator = (const AsteroidSpawner& rhs) = delete;
		~AsteroidSpawner() = default;

		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void OnDestroy() override;
		virtual std::unique_ptr<R2DScript> Clone() const override;

	private:
		std::unique_ptr<GameObject> asteroidPrefab;
		float spawnInterval;
		float currentTime;
		float asteroidVelY;
		float asteroidVelXRange;
		//int counter = 0;
	};
}

#endif // R_ASTEROID_SPAWNER_H_
