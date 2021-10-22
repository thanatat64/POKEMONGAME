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
	legendRate = 10;
	legendSpawn = 0;
	enemyTexture[0].loadFromFile("Textures/lv1.png");
	enemyTexture[1].loadFromFile("Textures/lv2.png");
	enemyTexture[2].loadFromFile("Textures/legendary.png");
	inGameTime = 0;
	bossAlive = false;
}

//functions
void Game::update(float deltaTime)
{
	inGameTime += deltaTime;
	player.update(deltaTime);
	bullet.update(deltaTime, player.getPosition(), player.getSize());
	currentSpawn += deltaTime;
	if (currentSpawn >= spawnRate && !bossAlive)
	{
		currentSpawn = 0;
		if (inGameTime >= 5 && inGameTime <=45)
		{
			enemies.push_back(Enemy(&enemyTexture[0], Vector2f(rand() % (SCREEN_WIDTH - 90), -95), Vector2f(90, 95), 100, 1));
		}
		else if (inGameTime >= 45)
		{
			int lvl = rand() % 2;
			enemies.push_back(Enemy(&enemyTexture[lvl], Vector2f(rand() % (SCREEN_WIDTH - 90), -95), Vector2f(90, 95), 100, lvl + 1));
		}
	}
	legendSpawn += deltaTime;
	if (legendSpawn >= legendRate && inGameTime >= 60)
	{
		legendSpawn = 0;	
		enemies.push_back(Enemy(&enemyTexture[2], Vector2f(rand() % (SCREEN_WIDTH - 180), -185), Vector2f(180, 185), 50, 3));
		legendRate = randint(40, 60);
		bossAlive = true;
	}
	for (size_t i = 0; i < enemies.size(); i++) // รัน enemy ทุกตัว
	{
		enemies[i].update(deltaTime);
		if (enemies[i].getPosition().y > SCREEN_HEIGHT)
		{
			if (enemies[i].getLevel()==3)
			{
				bossAlive = false;
			}
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
