#ifndef R_R2D_ENGINE_H_
#define R_R2D_ENGINE_H_

#include <functional>
#include <memory>
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

		const RenderEngine& GetRenderEngine();

		void Run(std::function<void(float)> updateMethod, std::function<void()> renderMethod);
		void Update(float dt);
		void ShutDown();

	private:
		std::unique_ptr <RenderEngine> renderEngine;
		std::unique_ptr <Input> input;
		
	};
}
#endif // !R_R2D_ENGINE_H_
