#pragma once
#include "HeaderBundle.h"
class Enemy
{
private:
	RectangleShape shape;
	Texture *enemyTexture;
	Vector2u enemyTextureSize;

	Vector2f direction;

	float speed;
	int level;
	int hp;
	int hpMax;
	//ทำระบบค่อยใส่เพิ่ม ex coin damage
public:
	Enemy(Texture *texture,Vector2f pos,Vector2f size,float speed,int level);
	void update(float deltaTime);
	void drawOn(RenderWindow* window);
	inline Vector2f getPosition() {return shape.getPosition();}
	inline Vector2f getSize() {return shape.getSize();}
	void setEnemyTexture();
	inline int getLevel() { return level; }
	inline FloatRect getGlobalBounds() { return shape.getGlobalBounds(); }
	inline void takeDamage(int damage) { hp -= damage; }
	inline int getHp() { return hp; }
	int getHpMax();
	
};

