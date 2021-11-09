#include "Menu.h"

Menu::Menu(RenderWindow* win, Game* g = nullptr)
{
	window = win;
	game = g;

	font.loadFromFile("font/Pokemon Solid.ttf");

	background.loadFromFile("Textures/Menubg.png");
	bg.setTexture(background);

	start.setup(Vector2f(140,285), Vector2f(340, 95), &font, "Start", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));
	scoreBoard.setup(Vector2f(140,410), Vector2f(340, 95), &font, "Scores", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));
	exit.setup(Vector2f(140,530), Vector2f(340, 95), &font, "Quit", Color(0, 0, 0, 50), Color(0, 0, 0, 80), Color(0, 0, 0, 120));


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
	//scoreBoard.update(mousePos, this, &Menu::toggleScoreBoard);
	exit.update<RenderWindow>(mousePos, window, &RenderWindow::close);

}

void Menu::render()
{
	window->draw(bg);
	start.render(*window);
	scoreBoard.render(*window);
	exit.render(*window);
}
