#include <iostream>
#include "Game.h"

int main(int argc, const char* argv[])
{
	Game game;
	game.Startup();
	game.Run();
	game.Shutdown();
}