#include "R2DEngine.h"
#include "GameConfig.h"
#include "RDebug.h"
#include "R2DGame.h"
#include "Screen.h"
#include "RTime.h"

//temp
#include "TextureManager.h"
#include "ShaderManager.h"

using namespace rb;

rb::R2DEngine::R2DEngine()
{
	Screen::width = GameConfig::windowWidth;
	Screen::height = GameConfig::windowHeight;
	renderEngine = std::make_unique<RenderEngine>(GameConfig::windowWidth, GameConfig::windowHeight, GameConfig::windowPosX, GameConfig::windowPosY, GameConfig::windowName);
	physicsEngine = std::make_unique<PhysicsEngine>();
	input = std::make_unique<Input>(renderEngine->Window());

	//temp
	ShaderManager::LoadShader("SpriteShader.vert", "SpriteShader.frag", Shader::ShaderType::SpriteShader);
	ShaderManager::LoadShader("AnimatedSprite.vert", "AnimatedSprite.frag", Shader::ShaderType::AnimatedSprite);
	TextureManager::LoadTexture("Explosion","explosion.png");
	animSprite = std::make_unique<AnimatedSprite>(TextureManager::GetTexture("Explosion"), 8, 3, 24, 0.05f, false);
}

RenderEngine* rb::R2DEngine::GetRenderEngine()
{
	return renderEngine.get();
}

PhysicsEngine* rb::R2DEngine::GetPhysicsEngine()
{
	return physicsEngine.get();
}

void rb::R2DEngine::Run(std::function<void(float)> OnUpdate)
{
	RTime::deltaTime = 0.0f;
	RTime::lastFrameTime = 0.0f;
	Debug::Log("Running engine...");
	while (!glfwWindowShouldClose(renderEngine->Window()))
	{
		RTime::elapsedTime = static_cast<float>(glfwGetTime());
		RTime::deltaTime = RTime::elapsedTime - RTime::lastFrameTime;
		RTime::lastFrameTime = RTime::elapsedTime;

		glfwPollEvents();
		//render
		renderEngine->PreRender();
		renderEngine->Render();
		animSprite->Render();
		//temp
		renderEngine->PostRender();
		
		//update
		physicsEngine->Update(RTime::deltaTime);
		assert(OnUpdate && "Update Method is null");
		OnUpdate(RTime::deltaTime);
		//temp
		animSprite->Update(RTime::deltaTime);

		Input::CleanUp();
	}
	glfwTerminate();
}

void rb::R2DEngine::ShutDown()
{
	glfwSetWindowShouldClose(renderEngine->Window(), GL_TRUE);
}
