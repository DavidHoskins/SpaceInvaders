#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "InputHandler.h"
#include "Button.h"

class MenuScreen
{
public:
	MenuScreen();

	void render(sf::RenderWindow& window);
	int update(InputHandler& gameInputHandler, sf::RenderWindow& window);
private:

	sf::RectangleShape m_BackGround;
	Button m_ScreenButtons[4];
};
#endif //!MENUSCREEN_H
