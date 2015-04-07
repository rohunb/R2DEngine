#include "TowerDefenseGame.h"
#include "RDebug.h"

rb::TowerDefenseGame::TowerDefenseGame()
{

}

void rb::TowerDefenseGame::StartGame()
{
	R2DGame::StartGame();
}

void rb::TowerDefenseGame::Update(float dt)
{
	//Debug::Log("TD Update " + ToString(dt));
}
