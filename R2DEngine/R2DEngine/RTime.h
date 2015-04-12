#ifndef R_TIME_H_
#define R_TIME_H_

namespace rb
{
	class RTime
	{
	public:
		RTime() = default;
		RTime(const RTime& rhs) = delete;
		RTime(RTime&& rhs) = delete;
		RTime& operator = (const RTime& rhs) = delete;
		RTime& operator = (RTime&& rhs) = delete;
		~RTime() = default;

		static float DeltaTime();
		static float ElapsedTime();

	private:
		static float deltaTime;
		static float elapsedTime;
		static float lastFrameTime;

		friend class R2DEngine;
	};
}

#endif // R_TIME_H_
