#pragma once
#include "HeaderBundle.h"
class Animation
{
private:
	Vector2u imageCount;
	Vector2u currentImage;

	float totalTime ;
	float switchTime;

public:
	Animation(Texture*texture,Vector2u imageCount,float switchTime);
	~Animation();
	Animation();
	void initialize(Texture* texture, Vector2u imageCount, float switchTime);
	void update(int row, float deltatime);

public:
	IntRect uvRect;
};

