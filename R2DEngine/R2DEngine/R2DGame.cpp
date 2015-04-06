#include "R2DGame.h"
#include <functional>
#include "RDebug.h"

using namespace rb;
using namespace std;
using namespace std::placeholders;

rb::R2DGame::R2DGame()
{
	engine = MakeUnique<R2DEngine>();
	engine->Run(bind(&R2DGame::Update,this, _1));
}
void rb::R2DGame::Update(float dt)
{
	Debug::Log("Game Update " + ToString(dt));
}
