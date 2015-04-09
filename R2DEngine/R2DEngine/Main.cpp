#include <memory>
#include "RocketCommand.h"

int main()
{
	using namespace rb;
	std::unique_ptr<RocketCommand> game = std::make_unique<RocketCommand>();
	game->StartGame();
}