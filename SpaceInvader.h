#ifndef SPACEINVADER_H
#define SPACEINVADER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "AlienHandler.h"
#include "NetworkHandler.h"
#include "Player.h"
#include "MenuScreen.h"


class SpaceInvader
{
public:
	//Constructor & Destructor.
	SpaceInvader();
	~SpaceInvader();
	//Public methods.
	void MainLoop();
	//Public enums.
	enum gameState { start, main, end, network};

private:
	//Private consts.
	const int m_kScreenWidth = 1920;
	const int m_kScreenHeight = 1080;

	//Private variables.
	gameState m_CurrentGameState;
	InputHandler m_CurrentInputHandler;
	Player m_CurrentPlayer[2];
	AlienHandler m_CurrentAliens;
	NetworkHandler m_CurrentNetworkHandler;
	MenuScreen m_CurrentMenuScreen;

	int m_iValue = 100;

	//Private methods.
	void render();
	void update();

	void networkUpdate();
	void networkRender(sf::RenderWindow* window);
	void localLogic();
	void networkLogic();

	void checkForEnd();
	void resetGame();

	void startMenuUpdate();
	void startMenuRender();

	//Private render variables.
	sf::RenderWindow* m_pWindow;
};

#endif //!SPACEINVADERS_H

