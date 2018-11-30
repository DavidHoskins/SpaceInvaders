#include "InputHandler.h"

//Returns true if key pressed.
bool InputHandler::keyPressed(sf::Keyboard::Key key)
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		return true;
	}
	return false;
}

//Returns true if button pressed.
bool InputHandler::joyStickButtonPressed(unsigned int joyStick, unsigned int button)
{
	sf::Joystick::update();
	if (sf::Joystick::isButtonPressed(joyStick, button))
	{
		return true;
	}
	return false;
}

//Returns the passed through axis's position.
float InputHandler::joyStickAxis(unsigned int joyStick, sf::Joystick::Axis axis)
{
	sf::Joystick::update();
	return sf::Joystick::getAxisPosition(joyStick, axis);
}

InputHandler::InputHandler()
{
}

//Input updates, if the player hits the esc key or the "back" button on an Xbox 360 controller will exit the game automatically.
void InputHandler::inputUpdate(sf::RenderWindow& window)
{
	m_fDeltaTime = m_Time.restart().asSeconds();

	if (keyPressed(sf::Keyboard::Escape))
	{
		window.close();
	}

	if (sf::Joystick::isConnected(1))
	{
		if (joyStickButtonPressed(1,6))
		{
			window.close();
		}
	}
}

//If the mouse is inside the object with the specified position and of specified size will return true.
bool InputHandler::mouseWithinBounds(sf::Vector2f position, sf::Vector2f size, sf::RenderWindow& window)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	if (mousePosition.x < (position.x + size.x) && mousePosition.x > position.x)
	{
		if (mousePosition.y < (position.y + size.y) && mousePosition.y > position.y)
		{
			return true;
		}
	}
	return false;
}

//returns whether the mouse button passed through has been selected.
bool InputHandler::mouseSelected(sf::Mouse::Button buttonToCheck)
{
	return sf::Mouse::isButtonPressed(buttonToCheck);
}
