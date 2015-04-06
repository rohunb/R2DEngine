#include "R2DEngine.h"
#include "GameConfig.h"
#include "RDebug.h"
#include "R2DGame.h"

rb::R2DEngine::R2DEngine()
{
	renderEngine = std::make_unique<RenderEngine>(GameConfig::windowWidth, GameConfig::windowHeight, GameConfig::windowPosX, GameConfig::windowPosY, GameConfig::windowName);
	input = std::make_unique<Input>(renderEngine->Window());
}


//void rb::R2DEngine::Run()
//{
//	float deltaTime = 0.0f;
//	float lastFrameTime = 0.0f;
//
//	while (!glfwWindowShouldClose(renderEngine->Window()))
//	{
//		float currentTime = static_cast<float>(glfwGetTime());
//		deltaTime = currentTime - lastFrameTime;
//		lastFrameTime = currentTime;
//
//		glfwPollEvents();
//		//render
//		renderEngine->PreRender();
//		renderEngine->PostRender();
//		//update
//		Update(deltaTime);
//	}
//	ShutDown();
//}

void rb::R2DEngine::Run(std::function<void(float)> updateMethod)
{
	float deltaTime = 0.0f;
	float lastFrameTime = 0.0f;

	while (!glfwWindowShouldClose(renderEngine->Window()))
	{
		float currentTime = static_cast<float>(glfwGetTime());
		deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		glfwPollEvents();
		//render
		renderEngine->PreRender();
		renderEngine->PostRender();
		//update
		Update(deltaTime);
		updateMethod(deltaTime);
	}
	ShutDown();
}

void rb::R2DEngine::Update(float dt)
{
	if (Input::GetKeyDown(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(renderEngine->Window(), GL_TRUE);
	}
	//game->Update(dt);
}

void rb::R2DEngine::ShutDown()
{
	glfwTerminate();
}
