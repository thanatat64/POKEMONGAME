#pragma once
#include"HeaderBundle.h"
using namespace sf;
using namespace std;

class Scene
{
protected:
	RenderWindow* window;

public:
	static int index;//การสร้าง ตัวแปล global
	inline Scene() { window = nullptr; }

	virtual void update(float deltaTime);
	virtual void render();
};