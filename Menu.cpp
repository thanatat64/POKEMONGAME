#include "Menu.h"

Menu::Menu(RenderWindow* win, Game* g = nullptr)
{
	window = win;
	game = g;

	font.loadFromFile("font/Pokemon Solid.ttf");
	typingFont.loadFromFile("font/minecraft.ttf");
	pixelFont.loadFromFile("font/pixel.ttf");

	background.loadFromFile("Textures/Menubg.png");
	bg.setTexture(background);

	goToScoreBoard = false;
	scoreBoardTexture.loadFromFile("Textures/scoreBoard.png");
	showScoreBoard.setTexture(scoreBoardTexture);

	start.setup(Vector2f(140,285), Vector2f(340, 95), &pixelFont, "Start", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));
	scoreBoard.setup(Vector2f(140,410), Vector2f(340, 95), &pixelFont, "Scores", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));
	exit.setup(Vector2f(140,530), Vector2f(340, 95), &pixelFont, "Quit", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));
	backToMenu.setup(Vector2f(110,670), Vector2f(240,80), &pixelFont, "Back to menu", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));

	start.setFontSize(30);
	scoreBoard.setFontSize(30);
	exit.setFontSize(30);

	start.isActive = true;
	scoreBoard.isActive = true;
	exit.isActive = true;
}

void startGame(int i, Game* game)
{
	game->reset();
	Scene::index=i;
}

void Menu::update(float deltaTime)
{
	mousePos = (Vector2f)Mouse::getPosition(*window);
	start.update<int, Game*>(mousePos, startGame, 1, game);
	scoreBoard.update(mousePos, this, &Menu::toggleScoreBoard);
	exit.update<RenderWindow>(mousePos, window, &RenderWindow::close);
	backToMenu.update(mousePos, this, &Menu::toggleScoreBoard);
}

void Menu::toggleScoreBoard()
{
	static bool toggle = true;
	if (toggle)
	{
		toggle = false;
		backToMenu.isActive = true;
		goToScoreBoard = true;
		start.isActive = false;
		scoreBoard.isActive = false;
		exit.isActive = false;
		
	}
	else
	{
		toggle = true;
		backToMenu.isActive = false;
		goToScoreBoard = false;
		start.isActive = true;
		scoreBoard.isActive = true;
		exit.isActive = true;
	}
}

void Menu::render()
{
	if (goToScoreBoard)
		window->draw(showScoreBoard);
	if (!goToScoreBoard)
		window->draw(bg);
	start.render(*window);
	scoreBoard.render(*window);
	exit.render(*window);
	backToMenu.render(*window);
}
