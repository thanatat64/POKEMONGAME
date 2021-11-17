#pragma once
#include "HeaderBundle.h"

class LeaderBoard
{
private:
	struct ScoreData
	{
		string playerName;
		int score;
	};
	Font pixelFont;

	Text numText[5];
	Text nameText[5];
	Text scoreText[5];

public:
	LeaderBoard();
	bool loadFromFile(string fileName);
	vector<ScoreData> datas;

	void sort();
	void addScore(string name, int score);
	void saveToFile(string fileName);
	void update();
	void render(RenderWindow* window);


};

