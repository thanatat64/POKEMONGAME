#pragma once
#include "HeaderBundle.h"
#include "Player.h"
#include "Bullet.h"
#include "Animation.h"
#include "Enemy.h"
class Game
{
private :
	RenderWindow* window; 
	Player player;
	Bullet bullet;
	vector<Enemy> enemies;
	float spawnRate;
	float currentSpawn;//lvl 1 2
	float legendRate;
	float legendSpawn;//legendary
	Texture enemyTexture[3];
	float inGameTime;
	bool bossAlive;

	//Vector2u enemyTextureSize;
public :
	Game(RenderWindow* window);
	void update(float deltaTime);
	void render();
};

