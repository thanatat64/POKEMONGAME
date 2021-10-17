#include "Enemy.h"

Enemy::Enemy(Texture* texture, Vector2f pos, Vector2f size, float speed)
{
	this->speed = speed;
	shape.setTexture(texture);
}

void Enemy::update(float deltaTime)
{

}

void Enemy::drawOn(RenderWindow* window)
{
}
