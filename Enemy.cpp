#include "Enemy.h"

Enemy::Enemy(Texture* texture, Vector2f pos, Vector2f size, float speed,int level)
{
	shape.setPosition(pos);
	shape.setSize(size);
	shape.setTexture(texture);
	this->speed = speed;
	this->level = level;
	this->hp = level;
	direction = Vector2f(0, 1);
	if (level == 1 || level == 2)
	{
		direction.x = randint(-1, 1);
	}

	if (level == 3)
	{
		hp += 7;
	}
	enemyTexture = texture;
	setEnemyTexture();
}

void Enemy::update(float deltaTime)
{
	shape.move(normalize(direction) * speed * deltaTime);
	if (shape.getPosition().x < 80)
	{
		shape.setPosition(Vector2f(80, shape.getPosition().y));
		direction.x = -direction.x;
	}
	if (shape.getPosition().x >1050)
	{
		shape.setPosition(Vector2f(1050, shape.getPosition().y));
		direction.x = -direction.x;
	}
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
