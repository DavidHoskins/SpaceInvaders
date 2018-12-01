#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

#include "GameObject.h"

class Button : public GameObject
{
public:

	virtual void render(sf::RenderWindow& window);
	virtual void update();

	Button(const sf::Font* buttonFont, const std::string& text, 
		const int characterSize, const sf::Vector2f& buttonPosition, 
		const sf::Vector2f& buttonSize, const sf::Color& buttonColor);
	~Button();

	void setHighlighted(const bool value) { m_highlighted = value; }
	bool getHighlighted() { return m_highlighted; }
private:
	sf::Text* m_buttonText;
	const float m_outlineThickness = 2.0f;

	bool m_highlighted;
	const sf::Color primaryColor = sf::Color::Black;
	const sf::Color secondaryColor = sf::Color::White;

	void updateHighlightStatus();
	void adjustText(sf::Text* textToAdjust);
};

#endif //!BUTTON_H
