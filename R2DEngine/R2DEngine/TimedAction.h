#ifndef R_TIMED_ACTION_H_
#define R_TIMED_ACTION_H_

#include <functional>
#include "R2DScript.h"

namespace rb
{
	class TimedAction : public R2DScript
	{
	public:
		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual std::unique_ptr<R2DScript> Clone() const override;
		
		void SetTimedAction(std::function<void()> action, float time);

	private:
		std::function<void()> action;
		float currentTime, timeToAction;
		bool startedTimer;
	};
}


#endif // R_TIMED_ACTION_H_
