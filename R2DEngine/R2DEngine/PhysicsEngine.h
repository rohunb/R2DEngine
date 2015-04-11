#ifndef R_PHYSICS_ENGINE_H_
#define R_PHYSICS_ENGINE_H_

#include <memory>
#include <vector>

namespace rb
{
	class PhysicsEngine
	{
	public:
		PhysicsEngine() = default;
		PhysicsEngine(const PhysicsEngine& rhs) = delete;
		PhysicsEngine(const PhysicsEngine&& rhs) = delete;
		PhysicsEngine& operator = (const PhysicsEngine& rhs) = delete;
		PhysicsEngine& operator = (PhysicsEngine&& rhs) = delete;
		~PhysicsEngine() = default;

		void AddNewRigidbody(std::shared_ptr<class Rigidbody2D>& rigidbody);
		void RemoveRigidbody(std::shared_ptr<class Rigidbody2D>& rigidbody);
		void Update(float dt);

	private:
		std::vector < std::shared_ptr<class Rigidbody2D>> rigidbodies;
	};
}

#endif // R_PHYSICS_ENGINE_H_
