#pragma once
#include "HeaderBundle.h"
#include "Player.h"
#include "Animation.h"
#include "Enemy.h"
#include "Ball.h"
class Game
{
private :
	RenderWindow* window; 
	Player player;
	vector<Enemy> enemies;
	vector<Ball> balls;
	float spawnRate;
	float currentSpawn;//lvl 1 2
	float legendRate;
	float legendSpawn;//legendary
	float fireRate;
	float fireSpawn;
	Texture enemyTexture[3];
	Texture ballTexture;
	float inGameTime;
	bool bossAlive;

	//Vector2u enemyTextureSize;
public :
	Game(RenderWindow* window);
	void update(float deltaTime);
	void render();
};

