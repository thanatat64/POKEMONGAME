#pragma once
#include "HeaderBundle.h"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox
{
private:
	Text textbox;
	ostringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	int limit;

	void inputLogic(int charTyped)
	{
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
		{
			text << static_cast<char>(charTyped);
		}
		else if (charTyped == DELETE_KEY)
		{
			if (text.str().length() > 0)
			{
				deleteLastChar();
			}
		}
		textbox.setString(text.str() + "_");
	}

	void deleteLastChar()
	{
		string t = text.str();
		string newText = "";
		for (int i = 0; i < t.length() - 1; i++)
		{
			newText += t[i];
		}
		text.str("");
		text << newText;

		textbox.setString(text.str());
	}

public:
	string getText() { return text.str(); }

	Textbox();

	Textbox(int size, sf::Color color, bool sel);

	inline void setFont(Font& font) { textbox.setFont(font); }

	inline void setPosition(Vector2f pos) { textbox.setPosition(pos); }

	inline void setLimit(bool ToF) { hasLimit = ToF; }

	inline void setLimit(bool ToF, int lim) 
	{
		hasLimit = ToF;
		limit = lim - 1;
	}

	void setSelected(bool sel);

	inline void drawOn(RenderWindow& window) { window.draw(textbox); }

	void typedOn(Event input);

	inline void TextEnter(Event event)
	{
		
	}
};

