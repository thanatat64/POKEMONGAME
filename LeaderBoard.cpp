#include "LeaderBoard.h"

LeaderBoard::LeaderBoard()
{
	pixelFont.loadFromFile("font/pixel.ttf");

	for (size_t i = 0; i < 5; i++)
	{
		numText[i].setFont(pixelFont);
		numText[i].setCharacterSize(30);
		numText[i].setPosition(425 - i * 75, 230 + i * 80);

		nameText[i].setFont(pixelFont);
		nameText[i].setCharacterSize(30);
		nameText[i].setPosition(500 - i * 75, 230 + i * 80);

		scoreText[i].setFont(pixelFont);
		scoreText[i].setCharacterSize(30);
		scoreText[i].setPosition(875 - i * 75, 230 + i * 80);
	}
}

bool LeaderBoard::loadFromFile(string fileName)
{
	ifstream file(fileName);
	if (file.bad())
	{
		return false;
	}

	datas.clear();

	for (int i = 0; i < 5; i++)
	{
		string strName;
		string strScore;
		if (!getline(file, strName))
		{
			break;
		}
		if (!getline(file, strScore))
		{
			break;
		}
		datas.push_back(ScoreData{ strName , stoi(strScore) });
	}
	file.close();
	return true;
}

void LeaderBoard::sort()
{
	for (int d = 0; d < datas.size(); d++)
	{
		for (int t = d + 1; t < datas.size(); t++)
		{
			if (datas[d].score < datas[t].score)
			{
				ScoreData temp = datas[d];
				datas[d] = datas[t];
				datas[t] = temp;
			}
		}
	}
}

void LeaderBoard::addScore(string name, int score)
{
	datas.push_back(ScoreData{ name,score });
	sort();
}

void LeaderBoard::saveToFile(string fileName)
{
	fstream file(fileName, ios::out);
	for (int i = 0; i < datas.size() && i < 5; i++)
	{
		file << datas[i].playerName << endl << datas[i].score << endl;
	}
	file.close();
}

void LeaderBoard::update()
{
	loadFromFile("score.txt");
	sort();
	for (int i = 0; i < datas.size(); i++)
	{
		nameText[i].setString(datas[i].playerName);
		scoreText[i].setString(std::to_string(datas[i].score));
	}
	saveToFile("score.txt");
}

void LeaderBoard::render(RenderWindow* window)
{
	for (size_t i = 0; i < 5; i++)
	{
		window->draw(numText[i]);
		window->draw(nameText[i]);
		window->draw(scoreText[i]);
	}
}
