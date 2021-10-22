#pragma once
#include "HeaderBundle.h"
#include "Animation.h"

class Player
{
private:
	RectangleShape shape;
	Vector2f velocity;
	Vector2f direction;
	float speed;
	Texture playerTexture;
	Animation animation;
	int row;
public:
	inline Player(Vector2f position=Vector2f(0,0), Vector2f size= Vector2f(90, 95), float speed=250)
	{
		this->shape.setPosition(position);
		this->shape.setSize(size);
		this->speed = speed;
		row = 0;
		setTextureAndAnimation();
	}
	inline void initialize(Vector2f position, Vector2f size, float speed)
	{
		this->shape.setPosition(position);
		this->shape.setSize(size);
		this->speed = speed;
	}
	inline void update(float deltaTime)
	{
		
		direction = Vector2f(0, 0);
		if (Keyboard::isKeyPressed(Keyboard::D) && shape.getPosition().x <= 1200 - shape.getSize().x)
		{
			row = 2;
			direction.x = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::A) && shape.getPosition().x >=0 )
		{
			row = 1;
			direction.x = -1;
		}
		if (Keyboard::isKeyPressed(Keyboard::W) && shape.getPosition().y /*>= 650*/ )
		{
			row = 3;
			direction.y = -1;
		}
		if (Keyboard::isKeyPressed(Keyboard::S) && shape.getPosition().y <= 900 - shape.getSize().y)
		{
			row = 0;
			direction.y = 1;
		}
		velocity = normalize(direction) * speed * deltaTime;
		shape.move(velocity);
		//animation update
		if (velocity == Vector2f() && row < 4)
		{
			row += 4;
		}
		animation.update(row, deltaTime);
		shape.setTextureRect(animation.uvRect);
	}

	inline void drawOn(RenderWindow *window)
	{
		window->draw(shape);
	}

	inline Vector2f getPosition()
	{
		return shape.getPosition();
	}

	inline FloatRect getGlobalBounds()
	{
		return shape.getGlobalBounds();
	}
	
	inline Vector2f getSize()
	{
		return shape.getSize();
	}

	inline void setTextureAndAnimation()
	{
		playerTexture.loadFromFile("Textures/pokemontrainer.png");
		shape.setTexture(&playerTexture);
		animation.initialize(&playerTexture, Vector2u(4, 8), 0.15f);
	}
};