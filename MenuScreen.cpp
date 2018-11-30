#include "MenuScreen.h"

//Constructor. 
MenuScreen:: MenuScreen()
{
	m_BackGround.setFillColor(sf::Color::Magenta);
	m_BackGround.setSize(sf::Vector2f(800.0f, 800.0f));

	std::string buttonTexts[] = {"Start", "Options", "Exit"};

	for (int i = 0; i < 4; i++)
	{
		m_ScreenButtons[i].setPosition(sf::Vector2f(200.0f, 100.0f + (i * 150.0f)));
	}
}

//Main render update method. Rendering goes here.
void MenuScreen::render(sf::RenderWindow& window)
{
	window.draw(m_BackGround);
	for (int i = 0; i < 4; i++)
	{
		m_ScreenButtons[i].render(window);
	}
}

//Main update method. Logic goes here.
int MenuScreen::update(InputHandler& currentHandler, sf::RenderWindow& window)
{
	for (int i = 0; i < 4; i++)
	{
		if (currentHandler.mouseWithinBounds(m_ScreenButtons[i].getPosition(), m_ScreenButtons[i].getSize(), window) && currentHandler.mouseSelected(sf::Mouse::Left))
		{
			return i;
		}
	}
	return -1;
}