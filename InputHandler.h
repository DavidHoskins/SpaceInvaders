#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>

class InputHandler
{
public:
	void inputUpdate(sf::RenderWindow& window);
	bool keyPressed(sf::Keyboard::Key key);

	bool joyStickButtonPressed(unsigned int joyStick, unsigned int button);
	float joyStickAxis(unsigned int joyStick, sf::Joystick::Axis axis);

	bool mouseWithinBounds(sf::Vector2f position, sf::Vector2f size, sf::RenderWindow& window);
	bool mouseSelected(sf::Mouse::Button buttonToCheck);

	const int m_kSpeed = 20;

	sf::Clock m_Time;
	float m_fDeltaTime;

	InputHandler();
};
#endif // !INPUTHANDLER_H

