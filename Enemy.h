#pragma once
#include "HeaderBundle.h"
class Enemy
{
private:
	RectangleShape shape;
	float speed;
	Texture *enemyTexture;
	Vector2u enemyTextureSize;
	int level;
	int hp;
	//ทำระบบค่อยใส่เพิ่ม ex coin damage
public:
	Enemy(Texture *texture,Vector2f pos,Vector2f size,float speed,int level);
	void update(float deltaTime);
	void drawOn(RenderWindow* window);
	inline Vector2f getPosition() {return shape.getPosition();}
	inline Vector2f getSize() {return shape.getSize();}
	void setEnemyTexture();
	inline int getLevel() { return level; }
};

