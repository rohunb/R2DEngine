#ifndef R_TIMED_DESTROY_H_
#define R_TIMED_DESTROY_H_

#include "R2DScript.h"

namespace rb
{
	class TimedDestroy : public R2DScript
	{
	public:
		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void OnDestroy() override;

		void StartDestroyTimer(float timeToDestroy);

	private:
		float currentTime;
		float timeToDestroy;
		bool startTimer;
	};
}
#endif // R_TIMED_DESTROY_H_