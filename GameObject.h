#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>

class GameObject : public sf::RectangleShape
{
public:
	//Constructor & Destructor.
	GameObject();
	~GameObject();

	//Virtual update functions.
	virtual void render(sf::RenderWindow& window) = 0;
	virtual void update() = 0;

	sf::Vector2f m_Position;
private:
};
#endif //!GAMEOBJECT_H

