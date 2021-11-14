#include "Ball.h"

Ball::Ball(Texture* texture,float speed,int size, Vector2f playerPos, Vector2f playerSize,int damage)
{
	shape.setTexture(texture);
	shape.setRadius(size);
	shape.setPosition(Vector2f(playerPos.x + (playerSize.x / 2) - shape.getRadius(), playerPos.y));
	this->speed = speed;
	this->damage = damage;
}

void Ball::drawOn(RenderWindow* window)
{
	window->draw(shape);
}
