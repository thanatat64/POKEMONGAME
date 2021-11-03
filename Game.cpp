#include "Game.h"
//Con/Des
Game::Game(RenderWindow* window)
{
	this->window = window;
	player.initialize(Vector2f(600, 550), Vector2f(90, 95), 250);

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
	fireRate = 0.8;
	fireSpawn = fireRate;
	pokeballTexture.loadFromFile("Textures/pokeball.png");
	ultraballTexture.loadFromFile("Textures/ultraball.png");
	masterballTexture.loadFromFile("Textures/masterball.png");

	//score
	score = 0;
	font.loadFromFile("font/Pokemon Solid.ttf");
	textScore.setFont(font);
	textScore.setFillColor(Color(64, 33, 28, 255));
	textScore.setCharacterSize(30);
	textScore.setPosition(Vector2f(30, 20));
	textScore.setString("Score " + to_string(score));

	//City HP
	cityHP = 5;
	HP.setFont(font);
	HP.setFillColor(Color::White);
	HP.setCharacterSize(25);
	HP.setPosition(Vector2f(30, 60));
	HP.setString("HP " + to_string(cityHP));
	
	//background foreground
	background.loadFromFile("Textures/background.png");
	bg.setTexture(background);
	foreground.loadFromFile("Textures/foreground.png");
	fg.setTexture(foreground);

}

//functions
void Game::update(float deltaTime)
{
	inGameTime += deltaTime;
	player.update(deltaTime);


#pragma region Ball
	fireSpawn += deltaTime;
	/*if (Keyboard::isKeyPressed(Keyboard::R))
	{
		if (&pokeballTexture)
		{
			swapball(pokeballTexture, ultraballTexture);
		}
	}*/
	//pokeball
	if (Keyboard::isKeyPressed(Keyboard::J) && fireSpawn >= fireRate)
	{
		fireSpawn = 0;
		balls.push_back(Ball(&pokeballTexture, 100, 15, player.getPosition(), player.getSize(), 1));
	}

	//ultraball
	if (Keyboard::isKeyPressed(Keyboard::K) && fireSpawn >= fireRate)
	{
		fireSpawn = 0;
		balls.push_back(Ball(&ultraballTexture, 100, 15, player.getPosition(), player.getSize(), 2));
	}

	//masterball
	if (Keyboard::isKeyPressed(Keyboard::L) && fireSpawn >= fireRate)
	{
		fireSpawn = 0;
		balls.push_back(Ball(&masterballTexture, 100, 15, player.getPosition(), player.getSize(), 10));
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
		if (inGameTime >= 5 && inGameTime <= 30)
		{
			enemies.push_back(Enemy(&enemyTexture[0], Vector2f(randint(100, 1020), -75), Vector2f(70, 75), 200, 1));
			enemies.push_back(Enemy(&enemyTexture[0], Vector2f(randint(100, 1020), -75), Vector2f(70, 75), 200, 1));
			enemies.push_back(Enemy(&enemyTexture[0], Vector2f(randint(100, 1020), -75), Vector2f(70, 75), 150, 1));
		}
		else if (inGameTime >= 30 && inGameTime <= 60)
		{
			int lvl = rand() % 2;
			enemies.push_back(Enemy(&enemyTexture[lvl], Vector2f(randint(100, 1020), -75), Vector2f(70, 75), 150, lvl + 1));
		}
		else if (inGameTime >= 60)
		{
			int lvl = rand() % 2;
			enemies.push_back(Enemy(&enemyTexture[lvl], Vector2f(randint(100, 1020), -75), Vector2f(70, 75), 150, lvl + 1));
			enemies.push_back(Enemy(&enemyTexture[0], Vector2f(randint(100, 1020), -75), Vector2f(70, 75), 200, 1));
		}
	}

	legendSpawn += deltaTime;
	if (legendSpawn >= legendRate && inGameTime >= 60)
	{
		legendSpawn = 0;
		enemies.push_back(Enemy(&enemyTexture[2], Vector2f(520, -185), Vector2f(180, 185), 50, 3));
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
			if (enemies[e].getHp() <= 0)
			{
				score += 10;
				textScore.setString("Score " + to_string(score));
			}
			else if (enemies[e].getPosition().y > SCREEN_HEIGHT)
			{
				cityHP -= 1;
				HP.setString("HP " + to_string(cityHP));
			}
			enemies.erase(enemies.begin() + e);
			continue;
		}
	}
#pragma endregion
}

void Game::render()
{
	window->draw(bg);
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
	window->draw(fg);
	//render score&HP
	window->draw(textScore);
	window->draw(HP);
}
