#pragma once
#include "HeaderBundle.h"
#include "Player.h"
#include "Bullet.h"
#include "Animation.h"
class Game
{
private :
	RenderWindow* window; 
	Player player;
	Bullet bullet;
public :
	Game(RenderWindow* window);
	void update(float deltaTime);
	void render();
};

