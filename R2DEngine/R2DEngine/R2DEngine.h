#ifndef R_R2D_ENGINE_H_
#define R_R2D_ENGINE_H_

#include <functional>
#include "RMemory.h"
#include "RenderEngine.h"
#include "RInput.h"

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

		const Input& GetInput();

		void Run(std::function<void(float)> updateMethod);
		void Update(float dt);
		void ShutDown();

	private:
		UniquePtr<RenderEngine> renderEngine;
		UniquePtr<Input> input;
		
	};
}
#endif // !R_R2D_ENGINE_H_
