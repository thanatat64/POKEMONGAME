#include "Enemy.h"

Enemy::Enemy(Texture* texture, Vector2f pos, Vector2f size, float speed)
{
	this->speed = speed;
	shape.setTexture(texture);
	shape.setPosition(pos);
	shape.setSize(size);
	
}

void Enemy::update(float deltaTime)
{
	shape.move(Vector2f(0, 1) * speed * deltaTime);
}

void Enemy::drawOn(RenderWindow* window)
{
	window->draw(shape);
}
