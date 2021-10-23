#pragma once
#include "HeaderBundle.h"

class Bullet
{
private:
	CircleShape bullet;
	bool active;
	Texture bulletTexture;
public:
	inline Bullet(int radius = 15)
	{
		active = false;
		this->bullet.setRadius(radius);
	}
	inline void initialize(int radius)
	{
		this->bullet.setRadius(radius);
	}
	inline void update(float deltaTime, Vector2f playerPos, Vector2f playerSize)
	{
		if (Keyboard::isKeyPressed(Keyboard::Space) && !active)
		{
			active = true;
			bullet.setPosition(Vector2f(playerPos.x + (playerSize.x / 2) - bullet.getRadius(), playerPos.y));
		}

		if (active)
		{
			bullet.move(Vector2f(0, -1) * 500.f * deltaTime);
			if (bullet.getPosition().y < 0)
			{
				active = false;
			}
		}
	}

	inline Vector2f getPosition()
	{
		return bullet.getPosition();
	}

	inline void drawOn(RenderWindow* window)
	{
		if (active)
		{
			window->draw(bullet);
		}
	}

	inline void setTexture()
	{
		bulletTexture.loadFromFile("Textures/pokeball.png");
		bullet.setTexture(&bulletTexture);
	}
};
