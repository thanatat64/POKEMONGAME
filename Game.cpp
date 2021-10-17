#include "Game.h"
//Con/Des
Game::Game(RenderWindow* window)
{
	this->window = window;
	player.initialize(Vector2f(720, 700), Vector2f(90, 95), 250);
	bullet.initialize(15);
	bullet.setTexture();
}

//functions
void Game::update(float deltaTime)
{
	player.update(deltaTime);
	bullet.update(deltaTime, player.getPosition(), player.getSize());

}

void Game::render()
{
	player.drawOn(window);
	bullet.drawOn(window);
}
