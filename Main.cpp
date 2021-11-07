#include "Game.h"


int main()
{
	RenderWindow window(VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT), "Game", Style::Titlebar | Style::Close);

	Game game(&window);
	srand(time(0));

	float deltaTime = 0.0f;//คือเวลาที่ใช้ใน 1 frame
	bool running = true;
	Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds() * running;
		Event ev;
		while (window.pollEvent(ev))
		{
			if (ev.type == Event::Closed)
				window.close();
			else if (ev.type == Event::KeyPressed)
			{
				if (ev.key.code == Keyboard::Escape)
				{
					window.close();
				}
				else if (ev.key.code == Keyboard::P)
				{
					running = !running;
				}
			}
			else if (ev.type == Event::TextEntered)
			{
				//cout << char(ev.text.unicode);
				//เอาไว้ใช่ตอนพิมชื่อ
			}
		}
		game.update(deltaTime);
		window.clear();
		game.render();
		window.display();
	}
	return 0;
}