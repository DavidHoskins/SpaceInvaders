#ifndef ALIENHANDLER_H
#define ALIENHANDLER_H

#include <SFML/System/Time.hpp>

#include "Alien.h"
#include "InputHandler.h"

class AlienHandler: public GameObject
{
private:

	const bool checkCanFire();
	const bool checkForEdge();

	const void moveAliens();

	//Fire variables.
	int m_iTimeSinceLastFire;
	const int m_kYimeToFire = 100000;

	int m_iSpeed;
	const int m_kSpeedIncrease = 20;
	const int m_kStartSpeed = 100;

	const int m_kAlienSpacing = 20;
	const int m_kAliensInLine = 5;

	bool m_bMoveLeft;

	InputHandler m_Timer;

	static const int m_kNumberOfAliens = 20;


	int m_iPoints;
public:
	//Constructor and Destructor.
	AlienHandler();
	~AlienHandler();

	virtual void render(sf::RenderWindow& window);
	virtual void update();
	void clientUpdate();

	const void resetAliens();
	const void restartTimer();

	void collisionDetection(Bullet* bullets);

	void setSpeed(int value){m_iSpeed = value;}
	const int getStartSpeed(){return m_kStartSpeed;}

	Alien m_Aliens[m_kNumberOfAliens];
};

#endif //!ALIENHANDLER_H

