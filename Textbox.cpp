#include "Textbox.h"

Textbox::Textbox()
{

}

Textbox::Textbox(int size, sf::Color color, bool sel)
{
	textbox.setCharacterSize(size);
	textbox.setFillColor(color);
	isSelected = true;
	if (sel)
	{
		textbox.setString("_");
	}
	else
	{
		textbox.setString(" ");
	}
}

void Textbox::setSelected(bool sel)
{
	isSelected = sel;
	if (!sel)
	{
		string t = text.str();
		string newText = "";
		for (int i = 0; i < t.length(); i++)
		{
			newText += t[i];
		}
		textbox.setString(newText);
	}
}

void Textbox::typedOn(Event input)
{
	if (isSelected)
	{
		int charTyped = input.text.unicode;
		if (charTyped < 128)
		{
			if (hasLimit)
			{
				if (text.str().length() <= limit)
				{
					inputLogic(charTyped);
				}
				else if (text.str().length() > limit && charTyped == DELETE_KEY)
				{
					deleteLastChar();
				}
			}
			else
			{
				inputLogic(charTyped);
			}
		}
	}
}
