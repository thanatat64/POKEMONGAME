#include "Enemy.h"

Enemy::Enemy(Texture* texture, Vector2f pos, Vector2f size, float speed,int level)
{
	shape.setPosition(pos);
	shape.setSize(size);
	shape.setTexture(texture);
	this->speed = speed;
	this->level = level;
	this->hp = level;
	if (level==3)
	{
		hp += rand();
	}
	enemyTexture = texture;
	setEnemyTexture();
}

void Enemy::update(float deltaTime)
{
	shape.move(Vector2f(0, 1) * speed * deltaTime);
}

void Enemy::drawOn(RenderWindow* window)
{
	window->draw(shape);
}

void Enemy::setEnemyTexture()
{
	if (level == 1 || level == 2)
	{
		enemyTextureSize = enemyTexture->getSize();
		enemyTextureSize.x /= 6;
		enemyTextureSize.y /= 6;
		shape.setTextureRect(
			IntRect(enemyTextureSize.x * (rand() % 6),
				enemyTextureSize.y * (rand() % 6),
				enemyTextureSize.x,
				enemyTextureSize.y));
	}
	else if (level == 3)
	{
		enemyTextureSize = enemyTexture->getSize();
		enemyTextureSize.x /= 3;
		enemyTextureSize.y /= 3;
		shape.setTextureRect(
			IntRect(enemyTextureSize.x * (rand() % 3),
				enemyTextureSize.y * (rand() % 3),
				enemyTextureSize.x,
				enemyTextureSize.y));
	}
	else
	{
		cout << "Set level" << endl;
	}
}
