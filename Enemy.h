#pragma once
#include "HeaderBundle.h"
class Enemy
{
private:
	RectangleShape shape;
	float speed;
	//ทำระบบค่อยใส่เพิ่ม ex coin damage
public:
	Enemy(Texture *texture,Vector2f pos,Vector2f size,float speed);
	void update(float deltaTime);
	void drawOn(RenderWindow* window);
};

