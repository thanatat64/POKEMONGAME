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
	float currentSpawn;
	Texture enemyTexture;
public :
	Game(RenderWindow* window);
	void update(float deltaTime);
	void render();
};

