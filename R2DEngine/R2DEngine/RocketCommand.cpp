#include "RocketCommand.h"
#include "RDebug.h"
#include "GameObject.h"

rb::RocketCommand::RocketCommand()
{
	/*testScene = std::make_shared<R2DScene>(CreateNewScene());
	missile = std::make_unique<GameObject>();
	testScene->Instantiate(*missile);*/
}

void rb::RocketCommand::StartGame()
{
	R2DGame::StartGame();
}


