#pragma once
#include "HeaderBundle.h"
class Item
{
private:
	RectangleShape shape;
	Texture* itemTexture;
	float speed;
public:
	bool died;
	Item(Texture* texture, float speed, Vector2f size,Vector2f enemyPos);
	inline Vector2f getPosition() { return shape.getPosition(); }
	inline FloatRect getGlobalBounds() { return shape.getGlobalBounds(); }
	void update(float deltaTime);
	void drawOn(RenderWindow* window);
};

