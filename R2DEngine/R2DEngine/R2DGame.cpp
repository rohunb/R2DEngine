#include "R2DGame.h"
#include "R2DEngine.h"

rb::R2DGame::R2DGame()
{
	engine = MakeUnique<R2DEngine>();
	engine->Run();
}
