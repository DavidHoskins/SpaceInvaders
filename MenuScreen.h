#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <iostream>

#include "InputHandler.h"
#include "Button.h"

class MenuScreen
{
public:
	MenuScreen();
	~MenuScreen();

	void render(sf::RenderWindow& window);
	int update(InputHandler& gameInputHandler, sf::RenderWindow& window);
private:
	sf::RectangleShape m_BackGround;

	static const int m_numberOfButtons = 4;
	Button* m_ScreenButtons[m_numberOfButtons];

	std::string buttonTexts[4] = { "Single", "Multi Server", "Multi Client", "Exit" };

	sf::Font* m_gameFont;
	const int m_characterSize = 40;

	sf::Sprite* m_spaceInvaderSprite;
	sf::Texture* m_spaceInvaderTexture;
};
#endif //!MENUSCREEN_H
