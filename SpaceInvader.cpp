#include "SpaceInvader.h"

//Main game render.
void SpaceInvader::render()
{
	m_pWindow->clear();
	for (int i = 0; i < 2; i++)
	{
		m_CurrentPlayer[i].render(*m_pWindow);
	}
	m_CurrentAliens.render(*m_pWindow);
	m_pWindow->display();
}

//Main update method.
void SpaceInvader::update()
{
	m_CurrentPlayer[0].setActive(true);
	for (int i = 0; i < 2; i++)
	{
		if (m_CurrentPlayer[i].getLivesLeft() > 0)
		{
			m_CurrentPlayer[i].update(1);
		}
		else if(i == 0)
		{
			m_CurrentPlayer[i].m_Position.x = -200;
			checkForEnd();
		}
		else
		{
			m_CurrentPlayer[i].m_Position.x = -200;
		}

		m_CurrentPlayer[i].collisionDetection(m_CurrentAliens.m_Aliens);
		m_CurrentAliens.collisionDetection(m_CurrentPlayer[i].m_Bullets);
	}
	m_CurrentAliens.update(m_kScreenWidth);
	m_CurrentInputHandler.inputUpdate(*m_pWindow);
}

//Main update for a multi-player game.
void SpaceInvader::networkUpdate()
{
	localLogic();
	render();
	networkLogic();
}

//Updates the player positions, aliens and other logic which needs to be calculated locally.
void SpaceInvader::localLogic()
{
	for (int i = 0; i < 2; i++)
	{
		if (m_CurrentNetworkHandler.m_iPlayerNum != -1)
		{
			if (m_CurrentPlayer[i].getLivesLeft() > 0)
			{
				m_CurrentPlayer[i].update(m_CurrentNetworkHandler.m_iPlayerNum);
			}
			else
			{
				m_CurrentPlayer[i].m_Position.x = -200;
				checkForEnd();
			}
		}
		else
		{
			if (m_CurrentPlayer[i].getLivesLeft() > 0)
			{
				m_CurrentPlayer[i].update(1);
			}
			else
			{
				m_CurrentPlayer[i].m_Position.x = -200;
			}
		}
		m_CurrentPlayer[i].collisionDetection(m_CurrentAliens.m_Aliens);
		m_CurrentAliens.collisionDetection(m_CurrentPlayer[i].m_Bullets);
	}
	m_CurrentAliens.update(m_kScreenWidth);
	m_CurrentInputHandler.inputUpdate(*m_pWindow);
}

//Checks whether the game is over, this should only get called after playerOne has ran out of lives.
void SpaceInvader::checkForEnd()
{
	if (!(m_CurrentPlayer[1].isActive()) || m_CurrentPlayer[1].getLivesLeft() <= 0)
	{
		m_CurrentGameState = end;
	}
}

//Logic to be handled by the network, sending and receiving data etc.
void SpaceInvader::networkLogic()
{
	if (m_CurrentNetworkHandler.m_bServer)
	{
		m_CurrentNetworkHandler.serverUpdate(m_CurrentPlayer, m_CurrentAliens.m_Aliens);
	}
	else
	{
		m_CurrentNetworkHandler.clientUpdate(m_CurrentPlayer[m_CurrentNetworkHandler.m_iPlayerNum], m_CurrentPlayer, m_CurrentAliens.m_Aliens);
	}
}

void SpaceInvader::networkRender(sf::RenderWindow* window)
{
	window->clear();
	for (int i = 0; i < 2; i++)
	{
		m_CurrentPlayer[i].render(*window);
	}
	m_CurrentAliens.render(*window);
	window->display();
}

//Resets all the data so the game is ready for a clean start.
void SpaceInvader::resetGame()
{
	for (int i = 0; i < 2; i++)
	{
		m_CurrentPlayer[i].setActive(false);
		m_CurrentPlayer[i].m_bIsNetworked = false;
		m_CurrentPlayer[i].setLivesLeft(3);
		m_CurrentPlayer[i].m_Position = sf::Vector2f((static_cast<float>(m_kScreenWidth) / 2.0f), (static_cast<float>(m_kScreenHeight) - m_CurrentPlayer[i].getSize().y));
	}
	m_CurrentAliens.setSpeed(m_CurrentAliens.getStartSpeed());
	m_CurrentAliens.resetAliens();
}

//Start menu logic update
void SpaceInvader::startMenuUpdate()
{
	int output = m_CurrentMenuScreen.update(m_CurrentInputHandler, *m_pWindow);
	resetGame();
	//This section works out what menu item the user selected was.
	if (output!= -1)
	{
		switch (output)
		{
		case 0:
			//Single player / local multi-player.
			m_CurrentGameState = main;
			m_CurrentAliens.restartTimer();
			break;
		case 1:
			//Server mode multi-player.
			m_CurrentNetworkHandler.startServer(m_CurrentPlayer, m_CurrentAliens.m_Aliens);
			m_CurrentGameState = network;
			m_CurrentAliens.restartTimer();
			break;
		case 2:
			//Client mode multi-player.
			m_CurrentNetworkHandler.m_bServer = false;
			m_CurrentNetworkHandler.clientStart(m_CurrentPlayer, m_CurrentAliens.m_Aliens);
			m_CurrentGameState = network;
			m_CurrentAliens.restartTimer();
			break;
		case 3:
			//Exit game.
			m_pWindow->close();
			break;
		default:
			break;
		}
	}
}

//Start menu rendering.
void SpaceInvader::startMenuRender()
{
	m_pWindow->clear();
	m_CurrentMenuScreen.render(*m_pWindow);
	m_pWindow->display();
}

//Main game loop.
void SpaceInvader::MainLoop()
{
	while (m_pWindow->isOpen())
	{
		switch (m_CurrentGameState)
		{
		case SpaceInvader::start:
			startMenuUpdate();
			startMenuRender();
			break;
		case SpaceInvader::main:
			update();
			render();
			break;
		case SpaceInvader::end:
			m_CurrentGameState = start;
			break;
		case SpaceInvader::network:
			networkUpdate();
			networkRender(m_pWindow);
			break;
		default:
			break;
		}
		sf::Event event;
		while (m_pWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_pWindow->close();
		}
	}
}

//Constructor.
SpaceInvader::SpaceInvader()
	:m_pWindow( new sf::RenderWindow(sf::VideoMode(m_kScreenWidth, m_kScreenHeight, 32), "Space Invaders", sf::Style::Default))
	, m_CurrentGameState(start)
{
	for (int i = 0; i < 2; i++)
	{
		m_CurrentPlayer[i].setPlayerNum((i+1));
		m_CurrentPlayer[i].m_Position = sf::Vector2f(static_cast<float>(m_kScreenWidth / 2), static_cast<float>(m_kScreenHeight) - 80.0f);
	}
	MainLoop();
}

//Destructor.
SpaceInvader::~SpaceInvader()
{
	delete m_pWindow;
}
