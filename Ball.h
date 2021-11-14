#pragma once
#include "HeaderBundle.h"
class Ball
{
private :
	CircleShape shape;
	Texture *ballTexture;
	float speed;
	int damage;
public :
	Ball(Texture* texture,float speed,int size, Vector2f playerPos, Vector2f playerSize,int damage);
	inline void update(float deltaTime)
	{
		shape.move(Vector2f(0, -1) * 500.f * deltaTime);
	}
	void drawOn(RenderWindow* window);
	inline Vector2f getPosition()
	{
		return shape.getPosition();
	}
	inline FloatRect getGlobalBounds() { return shape.getGlobalBounds(); }
	inline int getDamage() { return damage; }
};

