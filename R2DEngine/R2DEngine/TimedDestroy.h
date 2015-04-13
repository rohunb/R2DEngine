#ifndef R_TIMED_DESTROY_H_
#define R_TIMED_DESTROY_H_

#include "R2DScript.h"

namespace rb
{
	class TimedDestroy : public R2DScript
	{
	public:
		TimedDestroy() = default;
		TimedDestroy(const TimedDestroy& rhs) = delete;
		TimedDestroy& operator = (const TimedDestroy& rhs) = delete;
		~TimedDestroy() = default;

		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void OnDestroy() override;
		virtual std::unique_ptr<R2DScript> Clone() const override;

		void StartDestroyTimer(float timeToDestroy);


	private:
		float currentTime;
		float timeToDestroy;
		bool startTimer;
	};
}
#endif // R_TIMED_DESTROY_H_