#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

// contain IDLE, HOVER, and ACTIVE
enum class buttonState
{
	IDLE,
	HOVER,
	ACTIVE
};

// Clickable button with ability to callback
class Button
{
private:
	RectangleShape shape;
	Font* font = NULL;
	Text text;

	Color idle;
	Color hover;
	Color active;

	buttonState state = buttonState::IDLE;
	int offset;

	bool clickOutside;

public:
	bool isActive;

	Button();
	/// <summary>Constructor of Button class</summary>
	/// <param name="position">: Position of the button (top-left)</param>
	/// <param name="size">: Size of the button</param>
	/// <param name="font">: font pointer</param>
	/// <param name="text">: dunno what to say about. It's just button text.</param>
	/// <param name="idle">: Color when idle</param>
	/// <param name="hover">: Color when mouse is above the button</param>
	/// <param name="active">: Color when mouse clicked the button</param>
	Button(Vector2f position, Vector2f size, Font* font, string text, Color idle, Color hover, Color active);

	void setup(Vector2f position, Vector2f size, Font* font, string text, Color idle, Color hover, Color active);

	// draw the button on the window
	void render(RenderWindow& window);

	// return true if the button is pressed, false otherwise
	bool isPressed();

	// use if necessary
	// return state of the button
	// 3 states were IDLE, HOVER, and ACTIVE
	buttonState getButtonState();

	// set text of the button
	void setText(string text);
	// return text of the button as string
	string getText();

	// Self-explanatory
	void setFont(Font* font);
	// Self-explanatory
	const Font* getFont();
	// self-explanatory
	void setFontSize(unsigned int size);
	// Self-explanatory
	unsigned int getFontSize();
	// Same as button.setFontSize(button.getFontSize() + size);
	void increaseFontSizeBy(int size);

	/*
	update with an ability to callback
	How to use:
	* update<parameter type of callback function...>(mousePos, funcAddress, parameter of callback function...);
	* update<string, int>(mousePos, PrintNameAge, "User", 18);
	* update(mousePos, changePage);
	*/
	template <typename... Args>
	void update(Vector2f mousePos, void* funcAddress = nullptr, Args... args)
	{
		if (!isActive)
			return;

		bool leftClick = Mouse::isButtonPressed(Mouse::Left);
		if (leftClick && !shape.getGlobalBounds().contains(mousePos))
		{
			clickOutside = true;
		}
		else if (!leftClick)
		{
			clickOutside = false;
		}

		static bool once = true;
		state = buttonState::IDLE;
		if (shape.getGlobalBounds().contains(mousePos))
		{
			state = buttonState::HOVER;
			if (leftClick && !clickOutside)
			{
				state = buttonState::ACTIVE;
			}
		}

		switch (state)
		{
		case buttonState::IDLE:
			shape.setFillColor(idle);
			once = true;
			break;
		case buttonState::HOVER:
			shape.setFillColor(hover);
			once = true;
			break;
		case buttonState::ACTIVE:
			shape.setFillColor(active);
			if (funcAddress != nullptr && once)
			{
				once = false;
				typedef void(*Function)(Args...);
				Function Fptr = (Function)funcAddress;
				Fptr(args...);
			}
			break;
		default:
			cout << "State Error" << endl;
			break;
		}
	}

	// for callback member function with no argument
	// <Class, Member-func>(mousePos, Obj-pointer)
	template <typename TOwner, typename... Args>
	void update(Vector2f mousePos, TOwner* f, void(TOwner::* func)(Args...), Args... args)
	{
		if (!isActive)
			return;

		bool leftClick = Mouse::isButtonPressed(Mouse::Left);

		if (leftClick && !shape.getGlobalBounds().contains(mousePos))
		{
			clickOutside = true;
		}
		else if (!leftClick)
		{
			clickOutside = false;
		}

		static bool once = true;
		state = buttonState::IDLE;
		if (shape.getGlobalBounds().contains(mousePos))
		{
			state = buttonState::HOVER;
			if (leftClick && !clickOutside)
			{
				state = buttonState::ACTIVE;
			}
		}

		switch (state)
		{
		case buttonState::IDLE:
			shape.setFillColor(idle);
			once = true;
			break;
		case buttonState::HOVER:
			shape.setFillColor(hover);
			once = true;
			break;
		case buttonState::ACTIVE:
			shape.setFillColor(active);
			if (once)
			{
				once = false;
				(f->*func)(args...);
			}
			break;
		default:
			cout << "State Error" << endl;
			break;
		}
	}
};