#pragma once
#include "HeaderBundle.h"
#include "Game.h"
#include "Button.h"
#include "LeaderBoard.h"
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
	bool goToHTP;
	Sprite showHTP;
	Texture htpTexture;

	Button start;
	Button scoreBoard;
	Button exit;
	Button backToMenu;
	Button backToMenuhtp;
	Button htp;

	LeaderBoard leaderB;
public:
	Menu(RenderWindow* win, Game* g);

	void update(float deltaTime);
	void toggleScoreBoard();
	void toggleHTP();
	void render();
};

