#include "R2DEngine.h"
#include "GameConfig.h"

rb::R2DEngine::R2DEngine()
{
	renderEngine = std::make_unique<RenderEngine>(GameConfig::windowWidth, GameConfig::windowHeight, GameConfig::windowPosX, GameConfig::windowPosY, GameConfig::windowName);
		
}

void rb::R2DEngine::Run()
{
	while (!glfwWindowShouldClose(renderEngine->Window()))
	{
		glfwPollEvents();
		//render
		renderEngine->PreRender();
		renderEngine->PostRender();
		//update
	}
	ShutDown();
}

void rb::R2DEngine::Update(float dt)
{

}

void rb::R2DEngine::ShutDown()
{
	glfwTerminate();
}
