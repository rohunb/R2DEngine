#include <memory>
#include "RocketCommand.h"

int main()
{
	using namespace rb;
	auto& game = std::make_unique<RocketCommand>();
	game->StartGame();
}