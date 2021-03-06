#pragma once
#include "HeaderBundle.h"
#include "Player.h"
#include "Animation.h"
#include "Enemy.h"
#include "Ball.h"
#include "Item.h"
#include "Scene.h"
#include "LeaderBoard.h"
class Game : public Scene
{
private :
	RenderWindow* window; 
	Sprite bg;
	Texture background;
	Sprite fg;
	Texture foreground;
	Sprite ballMenu;
	Texture isballmenu;
	Sprite showGameOver;
	Texture gameOverBG;

	float inGameTime;
	bool bossAlive;
	bool gameOver;

	Player player;
	string playerName;
	Text nameText;
	
	Vector2f mousePos;
	Music battle;
	
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
	Font pixelFont;
	Text textScore;

	//enemyHP
	Text enemyHP;
	Text HpDown;

	//city HP
	int cityHP;
	Text HP;

	//ballcount
	int ultraballCount;
	int masterballCount;
	Text ulCount;
	Text masCount;
	Sprite infinity;
	Texture isInfinity;

	//Item
	vector<Item>SpBoosts;
	Sprite sBoost;
	Texture sBoostTexture;
	vector<Item>getUltraballs;
	vector<Item>getMasterballs;

	//LeaderBoard
	LeaderBoard leaderB;
public :
	Game(RenderWindow* window);
	void UpdateEnemyHP(int index);
	void UpdateEnemyHpDown(int index);
	inline string getName() { return this->playerName; }
	inline int getScore() { return this->score; }
	void update(float deltaTime);
	void render();
	void reset();

};

