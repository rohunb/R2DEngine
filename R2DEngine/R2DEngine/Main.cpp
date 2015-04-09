#include <memory>
#include "TowerDefenseGame.h"

int main()
{
	using namespace rb;
	std::unique_ptr<TowerDefenseGame> game = std::make_unique<TowerDefenseGame>();
	game->StartGame();
}