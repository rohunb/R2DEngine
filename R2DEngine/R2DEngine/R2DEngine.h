#ifndef R_R2D_ENGINE_H_
#define R_R2D_ENGINE_H_

#include "RMemory.h"
#include "RenderEngine.h"

namespace rb
{
	class R2DEngine
	{
	public:
		R2DEngine();
		R2DEngine(const R2DEngine& rhs) = delete;
		R2DEngine(const R2DEngine&& rhs) = delete;
		R2DEngine& operator = (const R2DEngine& rhs) = delete;
		R2DEngine& operator = (const R2DEngine&& rhs) = delete;
		~R2DEngine() = default;

		void Run();
		void Update(float dt);
		void ShutDown();

	private:
		bool keepRunning;
		UniquePtr<RenderEngine> renderEngine;

	};
}
#endif // !R_R2D_ENGINE_H_
