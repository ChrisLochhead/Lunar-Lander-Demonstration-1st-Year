#include"game.h"
#include"lander.h"

Game::Game(float igame)
{
	game = igame;
}

void Game::start()
{
	Lander lander(250, 450, 20);
}
