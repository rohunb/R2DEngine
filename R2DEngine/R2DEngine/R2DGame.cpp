#include "R2DGame.h"
#include <functional>
#include "RDebug.h"

using namespace rb;
using namespace std;
using namespace std::placeholders;

rb::R2DGame::R2DGame()
{
	Debug::Log("R2D Game ctor");
	engine = MakeUnique<R2DEngine>();
}

void rb::R2DGame::StartGame()
{
	engine->GetInput().RegisterKeyCallback(bind(&R2DGame::OnKeyboard, this, _1, _2));
	engine->Run(bind(&R2DGame::Update, this, _1));
}

void rb::R2DGame::Update(float dt)
{
	Debug::Log("Game Update " + ToString(dt));
}

void rb::R2DGame::OnKeyboard(int key, int action)
{
	Debug::Log("OnKeyboard: key " + ToString(key) + " action " + ToString(action));
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		engine->ShutDown();
	}
}

