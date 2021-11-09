#pragma once
#include "HeaderBundle.h"
#include "Game.h"
#include "Button.h"
class Menu : public Scene //inherit
{
private:
	Vector2f mousePos;
	Font font;
	Game* game;
	Sprite bg;
	Texture background;

	Button start;
	Button scoreBoard;
	Button exit;
public:
	Menu(RenderWindow* win, Game* g);

	void update(float deltaTime);
	void render();
};

