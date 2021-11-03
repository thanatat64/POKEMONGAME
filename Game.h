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
	Sprite bg;
	Texture background;
	Sprite fg;
	Texture foreground;

	float inGameTime;
	bool bossAlive;

	Player player;
	
	//Enemy
	vector<Enemy> enemies;
	float spawnRate;
	float currentSpawn;//lvl 1 2
	float legendRate;
	float legendSpawn;//legendary
	Texture enemyTexture[3];
	
	//ball
	vector<Ball> balls;
	float fireRate;
	float fireSpawn;
	Texture pokeballTexture;
	Texture ultraballTexture;
	Texture masterballTexture;

	//score
	int score;
	Font font;
	Text textScore;

	//city HP
	int cityHP;
	Text HP;

	//Vector2u enemyTextureSize;
public :
	Game(RenderWindow* window);
	void update(float deltaTime);
	void render();
};

