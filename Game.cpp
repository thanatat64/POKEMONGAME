#include "Game.h"
//Con/Des
Game::Game(RenderWindow* window)
{
	this->window = window;
	player.initialize(Vector2f(600, 550), Vector2f(90, 95), 350);
#pragma region Pokemon
	spawnRate = 5;
	currentSpawn = 0;
	legendRate = 10;
	legendSpawn = 0;
	enemyTexture[0].loadFromFile("Textures/lv1.png");
	enemyTexture[1].loadFromFile("Textures/lv2.png");
	enemyTexture[2].loadFromFile("Textures/legendary.png");
	inGameTime = 0;
	bossAlive = false;
#pragma endregion
#pragma region BALL
	fireRate = 0.8;
	fireSpawn = fireRate;
	pokeballTexture.loadFromFile("Textures/pokeball.png");
	ultraballTexture.loadFromFile("Textures/ultraball.png");
	masterballTexture.loadFromFile("Textures/masterball.png");
#pragma endregion
#pragma region Item
	sBoostTexture.loadFromFile("Textures/speed.png");
#pragma endregion
#pragma region background
	background.loadFromFile("Textures/background.png");
	bg.setTexture(background);
	foreground.loadFromFile("Textures/foreground.png");
	fg.setTexture(foreground);
#pragma endregion
#pragma region GAMEUI
	//score
	score = 0;
	font.loadFromFile("font/Pokemon Solid.ttf");
	textScore.setFont(font);
	textScore.setFillColor(Color(64, 33, 28, 255));
	textScore.setCharacterSize(30);
	textScore.setPosition(Vector2f(30, 20));
	textScore.setString("Score " + to_string(score));

	//HP
	enemyHP.setFont(font);
	enemyHP.setFillColor(Color::Black);
	enemyHP.setCharacterSize(10);

	//City HP
	cityHP = 10;
	HP.setFont(font);
	HP.setFillColor(Color::White);
	HP.setCharacterSize(25);
	HP.setPosition(Vector2f(30, 60));
	HP.setString("HP " + to_string(cityHP));

	//ballmenu
	ultraballCount = 0;
	masterballCount = 0;
	isballmenu.loadFromFile("Textures/ballMenu2.png");
	ballMenu.setTexture(isballmenu);
	ballMenu.setPosition(Vector2f(30, 100));
	isInfinity.loadFromFile("Textures/infinity2.png");
	infinity.setTexture(isInfinity);
	infinity.setPosition(Vector2f(75, 107));
	ulCount.setFont(font);
	ulCount.setFillColor(Color::White);
	ulCount.setCharacterSize(20);
	ulCount.setPosition(Vector2f(75, 137));
	ulCount.setString(to_string(ultraballCount));
	masCount.setFont(font);
	masCount.setFillColor(Color::White);
	masCount.setCharacterSize(20);
	masCount.setPosition(Vector2f(75, 168));
	masCount.setString(to_string(masterballCount));
#pragma endregion
}

void Game::UpdateEnemyHP(int index)
{
	enemyHP.setPosition(enemies[index].getPosition().x, enemies[index].getPosition().y - 15.f);
	enemyHP.setString("HP " +to_string(enemies[index].getHp()) + "/" +to_string(enemies[index].getHpMax()));
	HpDown.setPosition(enemies[index].getPosition().x, enemies[index].getPosition().y + 15.f);
}
void Game::UpdateEnemyHpDown(int index)
{
	HpDown.setString("- " + to_string(balls[index].getDamage()));
}

//functions
void Game::update(float deltaTime)
{
	inGameTime += deltaTime;
	player.update(deltaTime);
#pragma region Ball
	fireSpawn += deltaTime;
	//pokeball
	if (Keyboard::isKeyPressed(Keyboard::J) && fireSpawn >= fireRate)
	{
		fireSpawn = 0;
		balls.push_back(Ball(&pokeballTexture, 100, 15, player.getPosition(), player.getSize(), 1));
	}

	//ultraball
	else if (Keyboard::isKeyPressed(Keyboard::K) && fireSpawn >= fireRate)
	{
		fireSpawn = 0;
		if (ultraballCount > 0)
		{
			ultraballCount--;
			balls.push_back(Ball(&ultraballTexture, 100, 15, player.getPosition(), player.getSize(), 2));
		}
		ulCount.setString(to_string(ultraballCount));
	}

	//masterball
	else if (Keyboard::isKeyPressed(Keyboard::L) && fireSpawn >= fireRate)
	{
		fireSpawn = 0;
		if (masterballCount > 0)
		{
			masterballCount--;
			balls.push_back(Ball(&masterballTexture, 100, 15, player.getPosition(), player.getSize(), 10));
		}
		masCount.setString(to_string(masterballCount));
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
#pragma region Item
	//speedBoost
	for (size_t s = 0; s < SpBoosts.size(); s++)
	{
		SpBoosts[s].update(deltaTime);
		if (SpBoosts[s].died)
		{
			SpBoosts.erase(SpBoosts.begin() + s);
			continue;
		}
		if (player.getGlobalBounds().intersects(SpBoosts[s].getGlobalBounds()))
		{
			SpBoosts.erase(SpBoosts.begin() + s);
			player.setBoost(2);
		}
	}
	//ultraballItem
	for (size_t u = 0; u < getUltraballs.size(); u++)
	{
		getUltraballs[u].update(deltaTime);
		if (getUltraballs[u].died)
		{
			getUltraballs.erase(getUltraballs.begin() + u);
			continue;
		}
		if (player.getGlobalBounds().intersects(getUltraballs[u].getGlobalBounds()))
		{
			getUltraballs.erase(getUltraballs.begin() + u);
			ultraballCount++;
			ulCount.setString(to_string(ultraballCount));
		}
	}
	//masterballItem
	for (size_t m = 0; m < getMasterballs.size(); m++)
	{
		getMasterballs[m].update(deltaTime);
		if (getMasterballs[m].died)
		{
			getMasterballs.erase(getMasterballs.begin() + m);
			continue;
		}
		if (player.getGlobalBounds().intersects(getMasterballs[m].getGlobalBounds()))
		{
			getMasterballs.erase(getMasterballs.begin() + m);
			masterballCount++;
			masCount.setString(to_string(masterballCount));
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
				if (enemies[e].getHp() <= 0)
				{
						int rate = randint(1, 2);
					if (enemies[e].getLevel() == 1)
					{
						if (rate == 1)
						{
						SpBoosts.push_back(Item(&sBoostTexture, 10, Vector2f(36.5, 36.5), enemies[e].getPosition()));
						}
					}
					if (enemies[e].getLevel() == 2)
					{
						getUltraballs.push_back(Item(&ultraballTexture, 10, Vector2f(24, 24), enemies[e].getPosition()));
					}
					if (enemies[e].getLevel() == 3)
					{
						if (rate == 2)
						{
						getMasterballs.push_back(Item(&masterballTexture, 10, Vector2f(24, 24), enemies[e].getPosition()));
						}
					}
				}
				continue;
			}
		}
		if (enemies[e].getPosition().y > SCREEN_HEIGHT || enemies[e].getHp() <= 0)
		{
			if (enemies[e].getLevel() == 3)
			{
				bossAlive = false;
			}
			if (enemies[e].getHp() <= 0)
			{
				if (enemies[e].getLevel() == 1)
				{
					score += 10;
				}
				else if (enemies[e].getLevel() == 2)
				{
					score += 20;
				}
				else if (enemies[e].getLevel() == 3)
				{
					score += 100;
				}
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
		UpdateEnemyHpDown(i);
		window->draw(HpDown);
	}
	//render enemy
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies.at(i).drawOn(window);
		UpdateEnemyHP(i);
		window->draw(enemyHP);
	}
	//render SpBoostItem
	for (size_t i = 0; i < SpBoosts.size(); i++)
	{
		SpBoosts.at(i).drawOn(window);
	}
	//render ultraballItem
	for (size_t i = 0; i < getUltraballs.size(); i++)
	{
		getUltraballs.at(i).drawOn(window);
	}
	//render masterballItem
	for (size_t i = 0; i < getMasterballs.size(); i++)
	{
		getMasterballs.at(i).drawOn(window);
	}
	window->draw(fg);
	//render score&HP
	window->draw(ballMenu);
	window->draw(textScore);
	window->draw(HP);
	window->draw(infinity);
	window->draw(ulCount);
	window->draw(masCount);
}


