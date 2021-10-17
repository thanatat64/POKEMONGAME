#pragma once
#include "HeaderBundle.h"
class Enemy
{
private:
	RectangleShape shape;
	float speed;
	//���к������������ ex coin damage
public:
	Enemy(Texture *texture,Vector2f pos,Vector2f size,float speed);
	void update(float deltaTime);
	void drawOn(RenderWindow* window);
};

