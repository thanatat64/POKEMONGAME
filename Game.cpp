#include "Game.h"
//Con/Des
Game::Game(RenderWindow* window)
{
	this->window = window;
	player.initialize(Vector2f(720, 700), Vector2f(90, 95), 250);
	//Pokemon
	spawnRate = 5;
	currentSpawn = 0;
	legendRate = 10;
	legendSpawn = 0;
	enemyTexture[0].loadFromFile("Textures/lv1.png");
	enemyTexture[1].loadFromFile("Textures/lv2.png");
	enemyTexture[2].loadFromFile("Textures/legendary.png");
	inGameTime = 0;
	bossAlive = false;
	//BALL
	fireRate = 1;
	fireSpawn = fireRate;
	ballTexture.loadFromFile("Textures/pokeball.png");
}

//functions
void Game::update(float deltaTime)
{
	inGameTime += deltaTime;
	player.update(deltaTime);

#pragma region Ball
	fireSpawn += deltaTime;
	if (Keyboard::isKeyPressed(Keyboard::Space) && fireSpawn >= fireRate)
	{
		fireSpawn = 0;
		balls.push_back(Ball(&ballTexture, 100, 15, player.getPosition(), player.getSize(), 1));
	}
	for (size_t b = 0; b < balls.size(); b++)
	{
		balls[b].update(deltaTime);
		if (balls[b].getPosition().y < 0)
		{
			balls.erase(balls.begin() + b);
			continue;
		}
	}
#pragma endregion
#pragma region Pokemon
	currentSpawn += deltaTime;
	if (currentSpawn >= spawnRate && !bossAlive)
	{
		currentSpawn = 0;
		if (inGameTime >= 5 && inGameTime <= 45)
		{
			enemies.push_back(Enemy(&enemyTexture[0], Vector2f(rand() % (SCREEN_WIDTH - 90), -95), Vector2f(70, 70), 100, 1));
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
	for (size_t e = 0; e < enemies.size(); e++) // รัน enemy ทุกตัว
	{
		enemies[e].update(deltaTime);
		for (size_t b = 0; b < balls.size(); b++)
		{
			if (enemies[e].getGlobalBounds().intersects(balls[b].getGlobalBounds()))
			{
				enemies[e].takeDamage(balls[b].getDamage());
				balls.erase(balls.begin() + b);
				continue;
			}
		}
		if (enemies[e].getPosition().y > SCREEN_HEIGHT || enemies[e].getHp() <= 0 )
		{
			if (enemies[e].getLevel() == 3)
			{
				bossAlive = false;
			}
			enemies.erase(enemies.begin() + e);
			continue;
		}
	}
#pragma endregion
}

void Game::render()
{
	player.drawOn(window);
	// render ball
	for (size_t i = 0; i < balls.size(); i++)
	{
		balls.at(i).drawOn(window);
	}
	//render enemy
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies.at(i).drawOn(window);
	}
}
