#include "PhysicsEngine.h"
#include "Rigidbody2D.h"

using namespace rb;

void rb::PhysicsEngine::AddNewRigidbody(const Rigidbody2D& rigidbody)
{
	rigidbodies.push_back(std::make_shared<Rigidbody2D>(rigidbody));
}

void rb::PhysicsEngine::Update(float dt)
{

}
