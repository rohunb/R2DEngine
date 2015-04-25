#ifndef R_RENDER_ENGINE_H_
#define R_RENDER_ENGINE_H_

#include <vector>
#include <memory>
#include "GL_Includes.h"
#include <glfw3.h>
#include "RString.h"
#include "Colour.h"
#include "RMatrix.h"
#include "Shader.h"
#include "GameConfig.h"
#include "Texture.h"

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
		void PreRender();
		void Render();
		void PostRender();
		static void SetClearColour(const Colour& colour);

	private:
		GLFWwindow* window;
		Mat4 projection;
		static Colour clearColour;
		std::vector <std::shared_ptr<class SpriteRenderer>> spriteRenderers;
		std::vector <std::shared_ptr<class SpriteAnimator>> animatedSprites;

#if RENDER_MODE_INSTANCED
		struct TextureBatch
		{
			Texture texture;
			GLuint VAO;
			std::vector<Mat4> modelMatrices;
			std::vector<Colour> colours;
			explicit TextureBatch(const std::shared_ptr<class SpriteRenderer>& sprite);
		};
		struct ShaderBatch
		{
			Shader shader;
			std::vector<std::shared_ptr<TextureBatch>> textureBatches;
			explicit ShaderBatch(const std::shared_ptr<class SpriteRenderer>& sprite);
		};
		std::vector <std::shared_ptr<ShaderBatch>> shaderBatches;
		void SetupBatches();
		void ClearBatches();
#endif

	};
}

#endif // !R_RENDER_ENGINE_H_
