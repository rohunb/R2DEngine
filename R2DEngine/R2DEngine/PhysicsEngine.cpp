#include "PhysicsEngine.h"
#include <algorithm>
#include <assert.h>
#include "Rigidbody2D.h"

using namespace rb;

void rb::PhysicsEngine::AddNewRigidbody(std::shared_ptr<Rigidbody2D>& rigidbody)
{
	rigidbodies.push_back(rigidbody);
}

void rb::PhysicsEngine::RemoveRigidbody(std::shared_ptr<Rigidbody2D>& rigidbody)
{
	assert(std::find(rigidbodies.begin(), rigidbodies.end(), rigidbody) != rigidbodies.end() && "Rigidbody not found in PhysicsEngine");
	rigidbodies.erase(std::remove(rigidbodies.begin(), rigidbodies.end(), rigidbody),
						rigidbodies.end());
}

void rb::PhysicsEngine::Update(float dt)
{
	for (auto&& rigidbody: rigidbodies)
	{
		rigidbody->Update(dt);
	}
}
