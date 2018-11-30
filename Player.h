#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "Bullet.h"
#include "InputHandler.h"
#include "Alien.h"

class Player : public GameObject
{
private:
	InputHandler playerController;
	void inputUpdate(int playerNum);
	bool checkCanFire();

	bool checkAxis(unsigned int joyStick, sf::Joystick::Axis axis);
	void joystickInput();
	void keyboardInput();


	//private const variables.
	const int m_kSpeed = 600;
	const int m_kControllerSpeed = 5;
	const int m_kWidth = 50;
	const int m_kHeight = 50;
	const int m_kDeadZone = 1;

	//Changing this number changes the button used to fire the gun.
	const int m_kFireButNum = 0;

	static const int m_kNumberOfBullets = 20;

	int m_iFirePosition;
	int m_iPlayerNum;
	bool m_bActive;

	float m_fTimeSinceLastFire;

	int m_iLivesLeft = 3;


public:
	//Update methods.
	virtual void render(sf::RenderWindow& window);
	virtual void update(int playerNum);
	virtual void update(){};

	void collisionDetection(Alien* aliens);

	void setPlayerNum(int val){m_iPlayerNum = val;}
	int getPlayerNum(){return m_iPlayerNum;}
	bool isActive(){return m_bActive;}
	void setActive(bool val){m_bActive = val;}

	int getLivesLeft(){return m_iLivesLeft;}
	void setLivesLeft(int value){m_iLivesLeft = value;}

	bool m_bIsNetworked;
	bool m_bHasFired;
	bool m_bHasSent;
	bool m_bReleasedKey;

	void fireBullet(int playerNum);

	//Constructor & Destructor.
	Player();
	~Player();

	Bullet m_Bullets[m_kNumberOfBullets];



};

#endif //!PLAYER_H
