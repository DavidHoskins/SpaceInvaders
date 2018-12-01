#include "Button.h"

//Constructor.
Button::Button(const sf::Font* buttonFont, const std::string& text, 
	const int characterSize, const sf::Vector2f& buttonPosition, 
	const sf::Vector2f& buttonSize, const sf::Color& buttonColor)
	:m_highlighted(false)
{
	//Initialization button.
	setSize(buttonSize);
	setPosition(buttonPosition);
	setFillColor(buttonColor);

	//Initialization text.
	m_buttonText = new sf::Text(text, *buttonFont, characterSize);
	adjustText(m_buttonText);
	m_buttonText->setFillColor(primaryColor);
	m_buttonText->setOutlineColor(secondaryColor);
	m_buttonText->setOutlineThickness(m_outlineThickness);
}

//Destructor.
Button::~Button()
{
	delete m_buttonText;
}

//Adjusts text to fit in the center of the button.
void Button::adjustText(sf::Text* textToAdjust)
{
	sf::Vector2f newTextPosition(getPosition());
	newTextPosition.x += (getSize().x / 2);
	newTextPosition.x -= (textToAdjust->getGlobalBounds().width / 2);

	newTextPosition.y += (getSize().y / 2);
	newTextPosition.y -= (textToAdjust->getGlobalBounds().height / 1.5f);

	textToAdjust->setPosition(newTextPosition);
}



//Main render for button. Rendering goes here.
void Button::render(sf::RenderWindow& window)
{
	window.draw(*m_buttonText);
}

//Main update for button. Logic goes here.
void Button::update()
{
	updateHighlightStatus();
}

//Visually shows when player has highlighted an option.
void Button::updateHighlightStatus()
{
	if (m_highlighted)
	{
		m_buttonText->setFillColor(secondaryColor);
		m_buttonText->setOutlineColor(primaryColor);
	}
	else
	{
		m_buttonText->setFillColor(primaryColor);
		m_buttonText->setOutlineColor(secondaryColor);
	}
}
