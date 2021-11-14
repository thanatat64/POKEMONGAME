#pragma once
#include "HeaderBundle.h"
#include "Game.h"
#include "Button.h"
class Menu : public Scene //inherit
{
private:
	Vector2f mousePos;
	Font font;
	Font typingFont;
	Font pixelFont;
	Game* game;
	Sprite bg;
	Texture background;
	bool goToScoreBoard;
	Sprite showScoreBoard;
	Texture scoreBoardTexture;

	Button start;
	Button scoreBoard;
	Button exit;
	Button backToMenu;
public:
	Menu(RenderWindow* win, Game* g);

	void update(float deltaTime);
	void toggleScoreBoard();
	void render();
};

