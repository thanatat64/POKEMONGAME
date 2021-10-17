#pragma once
#include "HeaderBundle.h"
#include "Animation.h"

class Player
{
private:
	RectangleShape player;
	Vector2f velocity;
	Vector2f direction;
	float speed;
	Texture playerTexture;
	Animation animation;
	int row;
public:
	inline Player(Vector2f position=Vector2f(0,0), Vector2f size= Vector2f(90, 95), float speed=250)
	{
		this->player.setPosition(position);
		this->player.setSize(size);
		this->speed = speed;
		row = 0;
		setTextureAndAnimation();
	}
	inline void initialize(Vector2f position, Vector2f size, float speed)
	{
		this->player.setPosition(position);
		this->player.setSize(size);
		this->speed = speed;
	}
	inline void update(float deltaTime)
	{
		
		direction = Vector2f(0, 0);
		if (Keyboard::isKeyPressed(Keyboard::D) && player.getPosition().x <= 1200 - player.getSize().x)
		{
			row = 2;
			direction.x = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::A) && player.getPosition().x >=0 )
		{
			row = 1;
			direction.x = -1;
		}
		if (Keyboard::isKeyPressed(Keyboard::W) && player.getPosition().y /*>= 650*/ )
		{
			row = 3;
			direction.y = -1;
		}
		if (Keyboard::isKeyPressed(Keyboard::S) && player.getPosition().y <= 900 - player.getSize().y)
		{
			row = 0;
			direction.y = 1;
		}
		velocity = normalize(direction) * speed * deltaTime;
		player.move(velocity);
		//animation update
		if (velocity == Vector2f() && row < 4)
		{
			row += 4;
		}
		animation.update(row, deltaTime);
		player.setTextureRect(animation.uvRect);
	}

	inline void drawOn(RenderWindow *window)
	{
		window->draw(player);
	}

	inline Vector2f getPosition()
	{
		return player.getPosition();
	}

	inline FloatRect getGlobalBounds()
	{
		return player.getGlobalBounds();
	}
	
	inline Vector2f getSize()
	{
		return player.getSize();
	}

	inline void setTextureAndAnimation()
	{
		playerTexture.loadFromFile("Textures/pokemontrainer.png");
		player.setTexture(&playerTexture);
		animation.initialize(&playerTexture, Vector2u(4, 8), 0.15f);
	}
};