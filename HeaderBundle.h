#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900
using namespace std;
using namespace sf;

inline Vector2f normalize(Vector2f v)
{
	float length = sqrtf(v.x * v.x + v.y * v.y);
	return (length != 0) ? v / length : v;
}