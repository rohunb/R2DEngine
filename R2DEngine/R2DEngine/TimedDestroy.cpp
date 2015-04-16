#include "TimedDestroy.h"
#include "RTime.h"
#include "RDebug.h"

using namespace rb;

void rb::TimedDestroy::Start()
{
	timeToDestroy = 1.0f;
	currentTime = 0.0f;
}

void rb::TimedDestroy::Update(float dt)
{
	//Debug::Log("Destroy - Time: " + ToString(currentTime));
	if (startTimer && currentTime >= timeToDestroy)
	{
		Destroy(gameObject);
	}
	currentTime += dt;
}

void rb::TimedDestroy::OnDestroy()
{
}

void rb::TimedDestroy::StartDestroyTimer(float timeToDestroy)
{
	//Debug::Log("Start Timer :" + ToString(timeToDestroy));
	startTimer = true;
	currentTime = 0.0f;
	this->timeToDestroy = timeToDestroy;
}

std::unique_ptr<R2DScript> rb::TimedDestroy::Clone() const
{
	return std::make_unique<TimedDestroy>();
}
