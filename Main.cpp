#include "HeaderBundle.h"
#include "Scene.h"
#include "Game.h"
#include "Menu.h"


using namespace sf;
using namespace std;

float multiplier = 1;
vector<Event> textEvents = {};
int main()
{
	RenderWindow window(VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT), "Game", Style::Titlebar | Style::Close);
	srand(time(0));
	Game game(&window);
	Menu menu(&window,&game);

	vector<Scene*> sceneManagement;
	sceneManagement.push_back(&menu);
	sceneManagement.push_back(&game);

	float deltaTime = 0.0f;//คือเวลาที่ใช้ใน 1 frame
	Clock clock;

	while (window.isOpen())
	{
		textEvents.clear();
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
			else if (ev.type == Event::LostFocus)
			{
				multiplier = 0;
			}
			else if (ev.type == Event::GainedFocus)
			{
				multiplier = 1;
			}

			else if (ev.type == Event::TextEntered)
			{
				cout << char(ev.text.unicode);
				textEvents.push_back(ev);
			}
		}
		sceneManagement[Scene::index]->update(deltaTime);
		window.clear();
		sceneManagement[Scene::index]->render();
		window.display();
	}
	return 0;
}