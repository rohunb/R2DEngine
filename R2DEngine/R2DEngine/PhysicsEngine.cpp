#include "PhysicsEngine.h"
#include <algorithm>
#include <assert.h>
#include "Rigidbody2D.h"
#include "CircleCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "RVector.h"

using namespace rb;

void rb::PhysicsEngine::AddNewRigidbody(std::shared_ptr<Rigidbody2D>& rigidbody)
{
	assert(std::find(rigidbodies.begin(), rigidbodies.end(), rigidbody) == rigidbodies.end() && "Rigidbody already added to PhysicsEngine");
	rigidbodies.push_back(rigidbody);
}

void rb::PhysicsEngine::RemoveRigidbody(std::shared_ptr<Rigidbody2D>& rigidbody)
{
	assert(std::find(rigidbodies.begin(), rigidbodies.end(), rigidbody) != rigidbodies.end() && "Rigidbody not found in PhysicsEngine");
	rigidbodies.erase(std::remove(rigidbodies.begin(), rigidbodies.end(), rigidbody),
						rigidbodies.end());
}
void rb::PhysicsEngine::AddNewCollider(std::shared_ptr<Collider>& collider)
{
	assert(std::find(colliders.begin(), colliders.end(), collider) == colliders.end() && "Collider already added to Physics Engine");
	colliders.push_back(collider);
}

void rb::PhysicsEngine::RemoveCollider(std::shared_ptr<Collider>& collider)
{
	assert(std::find(colliders.begin(), colliders.end(), collider) != colliders.end() && "Collider not found");
	colliders.erase(std::remove(colliders.begin(), colliders.end(), collider), 
					colliders.end());
}

void rb::PhysicsEngine::Update(float dt)
{
	for (auto& rigidbody: rigidbodies)
	{
		rigidbody->Update(dt);
	}
}

bool rb::PhysicsEngine::CheckCollision(const CircleCollider& colA, const CircleCollider& colB)
{
	float distBetweenCircles = glm::distance(colA.GetGameObject()->GetTransform()->position, colB.GetGameObject()->GetTransform()->position);
	return distBetweenCircles < colA.GetRadius() + colB.GetRadius();
}
