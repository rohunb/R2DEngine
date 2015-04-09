#include "R2DEngine.h"
#include "GameConfig.h"
#include "RDebug.h"
#include "R2DGame.h"
//temp
#include "GameObject.h"

using namespace rb;

rb::R2DEngine::R2DEngine()
{
	renderEngine = std::make_unique<RenderEngine>(GameConfig::windowWidth, GameConfig::windowHeight, GameConfig::windowPosX, GameConfig::windowPosY, GameConfig::windowName);
	input = std::make_unique<Input>(renderEngine->Window());
}

const RenderEngine& rb::R2DEngine::GetRenderEngine()
{
	return *renderEngine;
}

void rb::R2DEngine::Run(std::function<void(float)> updateMethod, std::function<void()> renderMethod)
{
	float deltaTime = 0.0f;
	float lastFrameTime = 0.0f;
	Debug::Log("Running engine...");
	while (!glfwWindowShouldClose(renderEngine->Window()))
	{
		float currentTime = static_cast<float>(glfwGetTime());
		deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		glfwPollEvents();
		//render
		renderEngine->PreRender();
		assert(renderMethod && "Render method is null");
		renderMethod();
		renderEngine->PostRender();
		//update
		Update(deltaTime);
		assert(updateMethod && "Update Method is null");
		updateMethod(deltaTime);
	}
	glfwTerminate();

}

void rb::R2DEngine::Update(float dt)
{
	//game->Update(dt);
}

void rb::R2DEngine::ShutDown()
{
	glfwSetWindowShouldClose(renderEngine->Window(), GL_TRUE);
}
