#include "Game.h"
//Con/Des
Game::Game(RenderWindow* window)
{
	this->window = window;
	player.initialize(Vector2f(720, 700), Vector2f(90, 95), 250);
	bullet.initialize(15);
	bullet.setTexture();
	spawnRate = 5;
	currentSpawn = 0;
	enemyTexture.loadFromFile("Textures/pokemon.png");
}

//functions
void Game::update(float deltaTime)
{
	player.update(deltaTime);
	bullet.update(deltaTime, player.getPosition(), player.getSize());
	currentSpawn += deltaTime;
	if (currentSpawn >= spawnRate)
	{
		currentSpawn -= spawnRate;
		enemies.push_back(Enemy(&enemyTexture, Vector2f(rand() % (SCREEN_WIDTH - 90), -95), Vector2f(90, 95), 150));
	}
	for (size_t i = 0; i < enemies.size(); i++) // รัน enemy ทุกตัว
	{
		enemies[i].update(deltaTime);
		if (enemies[i].getPosition().y > SCREEN_HEIGHT)
		{
			enemies.erase(enemies.begin() + i);
		}
	}
}

void Game::render()
{
	player.drawOn(window);
	bullet.drawOn(window);
	for (size_t i = 0; i < enemies.size(); i++) // รัน enemy ทุกตัว
	{
		enemies.at(i).drawOn(window);
	}
}
