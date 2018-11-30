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

	Button();
private:
};

#endif //!BUTTON_H
