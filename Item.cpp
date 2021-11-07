#include "Item.h"

Item::Item(Texture* texture, float speed, Vector2f size, Vector2f enemyPos)
{
	shape.setTexture(texture);
	shape.setSize(size);
	shape.setPosition(enemyPos);
	this->speed = speed;
	this->died = false;
}

void Item::update(float deltaTime)
{
	shape.move(Vector2f(0, 1) * 200.f * deltaTime);
	if (shape.getPosition().y < 0 - shape.getGlobalBounds().height || shape.getPosition().y > SCREEN_HEIGHT)
	{
		died = true;
	}
}

void Item::drawOn(RenderWindow* window)
{
	window->draw(shape);
}
