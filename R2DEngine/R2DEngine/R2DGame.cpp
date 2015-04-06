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
	engine->Run(bind(&R2DGame::Update, this, _1));
}

void rb::R2DGame::Update(float dt)
{
	Debug::Log("Game Update " + ToString(dt));
}
