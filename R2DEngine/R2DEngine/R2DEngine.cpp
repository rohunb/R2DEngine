#include "R2DEngine.h"
#include "GameConfig.h"
#include "RDebug.h"
#include "R2DGame.h"
#include "Screen.h"

using namespace rb;

rb::R2DEngine::R2DEngine()
{
	Screen::width = GameConfig::windowWidth;
	Screen::height = GameConfig::windowHeight;
	renderEngine = std::make_unique<RenderEngine>(GameConfig::windowWidth, GameConfig::windowHeight, GameConfig::windowPosX, GameConfig::windowPosY, GameConfig::windowName);
	input = std::make_unique<Input>(renderEngine->Window());
}

RenderEngine& rb::R2DEngine::GetRenderEngine()
{
	return *renderEngine;
}

void rb::R2DEngine::Run(std::function<void(float)> updateMethod)
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
		renderEngine->Render();
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
