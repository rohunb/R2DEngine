#include "PhysicsEngine.h"
#include <algorithm>
#include <assert.h>
#include "Rigidbody2D.h"
#include "CircleCollider.h"
#include "RectCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "RVector.h"
#include "RDebug.h"

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
	auto& circleCol = std::dynamic_pointer_cast<CircleCollider>(collider);
	auto& rectCol = std::dynamic_pointer_cast<RectCollider>(collider);
	assert(circleCol || rectCol);
	if (circleCol)
	{
		assert(std::find(circleColliders.begin(), circleColliders.end(), circleCol) == circleColliders.end() && "Circle collider already added");
		circleColliders.push_back(circleCol);
	}
	else if (rectCol)
	{
		assert(std::find(rectColliders.begin(), rectColliders.end(), rectCol) == rectColliders.end() && "Rect collider already added");
		rectColliders.push_back(rectCol);
	}
	else
	{
		assert(false && "Neither circle nor rect");
	}
}

void rb::PhysicsEngine::RemoveCollider(std::shared_ptr<Collider>& collider)
{
	auto& circleCol = std::dynamic_pointer_cast<CircleCollider>(collider);
	auto& rectCol = std::dynamic_pointer_cast<RectCollider>(collider);
	assert(circleCol || rectCol);
	if (circleCol)
	{
		assert(std::find(circleColliders.begin(), circleColliders.end(), circleCol) != circleColliders.end() && "Circle collider not found");
		circleColliders.erase(std::remove(circleColliders.begin(), circleColliders.end(), circleCol), circleColliders.end());
	}
	else if (rectCol)
	{
		assert(std::find(rectColliders.begin(), rectColliders.end(), rectCol) != rectColliders.end() && "Rect collider already added");
		rectColliders.erase(std::remove(rectColliders.begin(), rectColliders.end(), rectCol), rectColliders.end());
	}
	else
	{
		assert(false && "Neither circle nor rect");
	}
}

void rb::PhysicsEngine::Update(float dt)
{
	for (auto& rigidbody : rigidbodies)
	{
		rigidbody->Update(dt);
	}
	if (circleColliders.size() == 0 && rectColliders.size() == 0)  return;
	
	for (size_t i = 0; i < circleColliders.size() -1; ++i)
	{
		for (size_t j = i+1; j < circleColliders.size(); ++j)
		{
			if (CheckCollision(*circleColliders[i], *circleColliders[j]))
			{
				//Debug::Log("Collision: Col A " + ToString(circleColliders[i]->GetGameObject()->GetTransform()->position) 
					//+ " col b " + ToString(circleColliders[j]->GetGameObject()->GetTransform()->position));
				circleColliders[i]->OnCollisionEnter(*circleColliders[j]);
				circleColliders[j]->OnCollisionEnter(*circleColliders[i]);
			}
		}
	}
}

bool rb::PhysicsEngine::CheckCollision(const CircleCollider& colA, const CircleCollider& colB)
{
	float distBetweenCircles = glm::distance(colA.GetGameObject()->GetTransform()->position, colB.GetGameObject()->GetTransform()->position);
	return distBetweenCircles <= colA.GetRadius() + colB.GetRadius();
}
