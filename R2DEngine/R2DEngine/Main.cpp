#include "TowerDefenseGame.h"
#include "RMemory.h"

int main()
{
	using namespace rb;
	UniquePtr<TowerDefenseGame> game = MakeUnique<TowerDefenseGame>();
	game->StartGame();
}