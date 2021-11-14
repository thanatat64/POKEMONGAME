#pragma once
#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

using namespace std;
using namespace sf;

extern float multiplier;

inline Vector2f normalize(Vector2f v)
{
	float length = sqrtf(v.x * v.x + v.y * v.y);
	return (length != 0) ? v / length : v;
}
inline int randint(int start, int stop)
{
	return rand() % (stop - start + 1) + start;
}
inline Texture swapball(Texture a, Texture b)
{
	Texture c;
	c = b;
	b = a;
	a = c;
}