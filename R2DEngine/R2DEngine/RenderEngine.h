#ifndef R_RENDER_ENGINE_H_
#define R_RENDER_ENGINE_H_

#include <vector>
#include <memory>
#include "GL_Includes.h"
#include <glfw3.h>
#include "RString.h"
#include "Colour.h"

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
		~RenderEngine() = default;

		GLFWwindow* Window() const;

		void AddNewRenderer(std::shared_ptr<class SpriteRenderer>& renderer);
		void RemoveRenderer(std::shared_ptr<class SpriteRenderer>& renderer);
		void PreRender() const;
		void Render() const;
		void PostRender() const;
		static void SetClearColour(const Colour& colour);

	private:
		GLFWwindow* window;
		static Colour clearColour;
		std::vector<std::shared_ptr<class SpriteRenderer>> spriteRenderers;

	};
}

#endif // !R_RENDER_ENGINE_H_
