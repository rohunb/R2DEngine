#include "PhysicsEngine.h"
#include "Rigidbody2D.h"

using namespace rb;

//void rb::PhysicsEngine::AddNewRigidbody(const Rigidbody2D& rigidbody)
//{
//}

void rb::PhysicsEngine::AddNewRigidbody(std::shared_ptr<Rigidbody2D>& rigidbody)
{
	rigidbodies.push_back(rigidbody);
}

void rb::PhysicsEngine::Update(float dt)
{
	for (auto&& rigidbody: rigidbodies)
	{
		rigidbody->Update(dt);
	}
}
