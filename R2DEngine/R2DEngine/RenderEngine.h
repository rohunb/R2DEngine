#ifndef R_RENDER_ENGINE_H_
#define R_RENDER_ENGINE_H_

#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include "RString.h"

namespace rb
{
	class RenderEngine
	{
	public:
		RenderEngine(int windowWidth, int windowHeight, int windowPosX, int windowPosY, string windowName);
		RenderEngine(const RenderEngine& rhs) = delete;
		RenderEngine(const RenderEngine&& rhs) = delete;
		RenderEngine& operator = (const RenderEngine& rhs) = delete;
		RenderEngine& operator = (const RenderEngine&& rhs) = delete;
		~RenderEngine() =default;

		GLFWwindow* Window() const;

		void PreRender() const;
		void PostRender() const;

	private:
		GLFWwindow* window;
	};
}

#endif // !R_RENDER_ENGINE_H_
