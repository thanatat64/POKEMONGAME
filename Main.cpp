#include "Game.h"


int main()
{
	RenderWindow window(VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT), "Game", Style::Titlebar | Style::Close);

	Game game(&window);
	srand(time(0));

	/*ต้องย้ายเข้า class barier--------------------------
	RectangleShape tree1(Vector2f(220, 117.5));
	tree1.setPosition(150, 550);
	Texture Treetexture;
	Treetexture.loadFromFile("Textures/tree.png");
	tree1.setTexture(&Treetexture);

	RectangleShape tree2(Vector2f(220, 117.5));
	tree2.setPosition(820, 550);
	Texture Tree2texture;
	Tree2texture.loadFromFile("Textures/tree.png");
	tree2.setTexture(&Tree2texture);
	ต้องย้ายเข้า class barier----------------------------*/

	
	float deltaTime = 0.0f;//คือเวลาที่ใช้ใน 1 frame
	Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
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
			}
			else if (ev.type == Event::TextEntered)
			{
				//cout << char(ev.text.unicode);
				//เอาไว้ใช่ตอนพิมชื่อ
			}
		}
		game.update(deltaTime);
		window.clear(Color(88, 186, 145, 255));
		game.render();
		window.display();
	}
	return 0;
}