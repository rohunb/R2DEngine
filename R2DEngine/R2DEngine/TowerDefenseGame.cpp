#include "TowerDefenseGame.h"
#include "RDebug.h"

rb::TowerDefenseGame::TowerDefenseGame()
{
	Debug::Log("TD ctor");

}

void rb::TowerDefenseGame::StartGame()
{
	R2DGame::StartGame();
}

void rb::TowerDefenseGame::Update(float dt)
{
	//Debug::Log("TD Update " + ToString(dt));
}
