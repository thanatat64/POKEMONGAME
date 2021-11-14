#include "Button.h"

using namespace sf;
using namespace std;

constexpr int OFFRATIO = 3;

Button::Button()
{
	this->font = nullptr;
	isActive = false;
	clickOutside = false;
	offset = 0;
}

Button::Button(Vector2f position, Vector2f size, Font* font, string text, Color idle, Color hover, Color active)
{
	shape.setPosition(position);
	shape.setSize(size);
	shape.setFillColor(idle);

	clickOutside = false;
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(Color::White);
	this->text.setCharacterSize(24);

	offset = this->text.getCharacterSize() / OFFRATIO;
	Vector2f textBoxSize = Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height);
	this->text.setPosition((shape.getSize() / 2.f) - (textBoxSize / 2.f) + (shape.getPosition()) + Vector2f(0, -offset));

	this->idle = idle;
	this->hover = hover;
	this->active = active;
	isActive = false;
}

void Button::setup(Vector2f position, Vector2f size, Font* font, string text, Color idle, Color hover, Color active)
{
	shape.setPosition(position);
	shape.setSize(size);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(Color::White);
	this->text.setCharacterSize(24);

	offset = this->text.getCharacterSize() / OFFRATIO;
	Vector2f textBoxSize = Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height);
	this->text.setPosition((shape.getSize() / 2.f) - (textBoxSize / 2.f) + (shape.getPosition()) + Vector2f(0, -offset));

	this->idle = idle;
	this->hover = hover;
	this->active = active;

	shape.setFillColor(this->idle);
}

void Button::render(RenderWindow& window)
{
	if (isActive)
	{
		window.draw(shape);
		window.draw(text);
	}
}

bool Button::isPressed()
{
	return (state == buttonState::ACTIVE) ? true : false;
}

buttonState Button::getButtonState()
{
	return state;
}

void Button::setText(string text)
{
	this->text.setString(text);
	Vector2f textBoxSize = Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height);
	this->text.setPosition((shape.getSize() / 2.f) - (textBoxSize / 2.f) + (shape.getPosition()) + Vector2f(0, -offset));
}

string Button::getText()
{
	return text.getString();
}

void Button::setFont(Font* font)
{
	this->text.setFont(*this->font);
	Vector2f textBoxSize = Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height);
	this->text.setPosition((shape.getSize() / 2.f) - (textBoxSize / 2.f) + (shape.getPosition()) + Vector2f(0, -offset));
}

const Font* Button::getFont()
{
	return text.getFont();
}

void Button::setFontSize(unsigned int size)
{
	text.setCharacterSize(size);
	offset = size / OFFRATIO;
	Vector2f textBoxSize = Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height);
	this->text.setPosition((shape.getSize() / 2.f) - (textBoxSize / 2.f) + (shape.getPosition()) + Vector2f(0, -offset));
}

unsigned int Button::getFontSize()
{
	return text.getCharacterSize();
}

void Button::increaseFontSizeBy(int size)
{
	setFontSize(text.getCharacterSize() + size);
}