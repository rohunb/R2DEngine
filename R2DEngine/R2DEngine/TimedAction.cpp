#include "TimedAction.h"

using namespace rb;

void rb::TimedAction::Start()
{
	currentTime = 0.0f;
	timeToAction = 0.0f;
	action = nullptr;
	startedTimer = false;
}

void rb::TimedAction::Update(float dt)
{
	if (startedTimer)
	{
		if (currentTime >= timeToAction)
		{
			action();
			startedTimer = false;
		}
		currentTime += dt;
	}
}

std::unique_ptr<R2DScript> rb::TimedAction::Clone() const
{
	return std::make_unique<TimedAction>();
}

void rb::TimedAction::SetTimedAction(std::function<void()> action, float time)
{
	this->action = action;
	this->timeToAction = time;
	startedTimer = true;
}
