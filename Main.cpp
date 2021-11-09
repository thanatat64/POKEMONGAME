#include "HeaderBundle.h"
#include "Scene.h"
#include "Game.h"
#include "Menu.h"


using namespace sf;
using namespace std;

float multiplier = 1;

int main()
{
	RenderWindow window(VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT), "Game", Style::Titlebar | Style::Close);
	srand(time(0));

	Game game(&window);
	Menu menu(&window,&game);

	vector<Scene*> sceneManagement;
	sceneManagement.push_back(&menu);
	sceneManagement.push_back(&game);

	float deltaTime = 0.0f;//������ҷ����� 1 frame
	Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds() * multiplier;
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
					multiplier = !multiplier;
				}
			}
			else if (ev.type == Event::TextEntered)
			{
				//cout << char(ev.text.unicode);
				//��������͹�������
			}
		}
		sceneManagement[Scene::index]->update(deltaTime);
		window.clear();
		sceneManagement[Scene::index]->render();
		window.display();
	}
	return 0;
}