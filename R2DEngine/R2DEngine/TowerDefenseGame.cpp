#include "TowerDefenseGame.h"
#include "RDebug.h"

rb::TowerDefenseGame::TowerDefenseGame()
{

}

void rb::TowerDefenseGame::StartGame()
{
	R2DGame::StartGame();
}

void rb::TowerDefenseGame::Render()
{
	R2DGame::Render();
	//Debug::Log("TD Render");
}

void rb::TowerDefenseGame::Update(float dt)
{
	R2DGame::Update(dt);
 	//Debug::Log("TD Update " + ToString(dt));
}
