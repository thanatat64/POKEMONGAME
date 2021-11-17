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

	goToHTP = false;
	htpTexture.loadFromFile("Textures/HTP.png");
	showHTP.setTexture(htpTexture);

	start.setup(Vector2f(140, 285), Vector2f(340, 95), &pixelFont, "Start", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));
	scoreBoard.setup(Vector2f(140, 410), Vector2f(340, 95), &pixelFont, "Scores", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));
	htp.setup(Vector2f(1120, 820), Vector2f(50, 50), &pixelFont, " ? ", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));
	exit.setup(Vector2f(140, 530), Vector2f(340, 95), &pixelFont, "Quit", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));
	backToMenu.setup(Vector2f(110, 670), Vector2f(240, 80), &pixelFont, "Back to menu", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));
	backToMenuhtp.setup(Vector2f(45, 760), Vector2f(240, 80), &pixelFont, "Back to menu", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));

	start.setFontSize(30);
	scoreBoard.setFontSize(30);
	exit.setFontSize(30);
	htp.setFontSize(30);

	start.isActive = true;
	scoreBoard.isActive = true;
	exit.isActive = true;
	htp.isActive = true;
}

void startGame(int i, Game* game)
{
	game->reset();
	Scene::index = i;
}

void Menu::update(float deltaTime)
{
	mousePos = (Vector2f)Mouse::getPosition(*window);
	start.update<int, Game*>(mousePos, startGame, 1, game);
	scoreBoard.update(mousePos, this, &Menu::toggleScoreBoard);
	htp.update(mousePos, this, &Menu::toggleHTP);
	exit.update<RenderWindow>(mousePos, window, &RenderWindow::close);
	backToMenu.update(mousePos, this, &Menu::toggleScoreBoard);
	backToMenuhtp.update(mousePos, this, &Menu::toggleHTP);
}

void Menu::toggleScoreBoard()
{
	static bool toggle = true;
	if (toggle)
	{
		toggle = false;
		goToScoreBoard = true;
		leaderB.update();
		goToHTP = false;
		//button
		backToMenu.isActive = true;
		start.isActive = false;
		scoreBoard.isActive = false;
		exit.isActive = false;
		htp.isActive = false;
		//button
	}
	else
	{
		toggle = true;
		goToScoreBoard = false;
		goToHTP = false;
		//button
		backToMenu.isActive = false;
		start.isActive = true;
		scoreBoard.isActive = true;
		exit.isActive = true;
		htp.isActive = true;
		//button
	}
}

void Menu::toggleHTP()
{
	static bool toggle2 = true;
	if (toggle2)
	{
		toggle2 = false;
		goToHTP = true;
		goToScoreBoard = false;
		//button
		backToMenuhtp.isActive = true;
		backToMenu.isActive = false;
		start.isActive = false;
		scoreBoard.isActive = false;
		exit.isActive = false;
		htp.isActive = false;
		//button
	}
	else
	{
		toggle2 = true;
		goToScoreBoard = false;
		goToHTP = false;
		//button
		backToMenuhtp.isActive = false;
		backToMenu.isActive = false;
		start.isActive = true;
		scoreBoard.isActive = true;
		exit.isActive = true;
		htp.isActive = true;
		//button
	}
}

void Menu::render()
{
	if (goToScoreBoard && !goToHTP)
	{
		window->draw(showScoreBoard);
		leaderB.render(window);
	}
	if (goToHTP && !goToScoreBoard)
	{
		window->draw(showHTP);
	}
	if (!goToScoreBoard && !goToHTP)
		window->draw(bg);
	start.render(*window);
	scoreBoard.render(*window);
	exit.render(*window);
	backToMenu.render(*window);
	backToMenuhtp.render(*window);
	htp.render(*window);
}
