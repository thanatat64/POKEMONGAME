#pragma once
#include "HeaderBundle.h"
class Ball
{
private :
	//pokeball
	CircleShape shape;
	Texture *ballTexture;
	//ultraball
	
	//masterball

	float speed;
	int damage;
public :
	Ball(Texture* texture,float speed,int size, Vector2f playerPos, Vector2f playerSize,int damage);
	void update(float deltaTime);
	void drawOn(RenderWindow* window);
	inline Vector2f getPosition(){return shape.getPosition();}
	inline FloatRect getGlobalBounds() { return shape.getGlobalBounds(); }
	inline int getDamage() { return damage; }
};

