#include "Button.h"

//Main render for button. Rendering goes here.
void Button::render(sf::RenderWindow& window)
{
	window.draw(*this);
}

//Main update for button. Logic goes here.
void Button::update()
{

}

//Constructor.
Button::Button()
{
	setSize(sf::Vector2f(100.0f, 50.0f));
}