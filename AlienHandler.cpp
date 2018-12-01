#include "AlienHandler.h"

//Constructor.
AlienHandler::AlienHandler()
	:m_bMoveLeft(false)
	,m_iPoints(0)
	,m_iSpeed(m_kStartSpeed)
{
	m_alienTexture = new sf::Texture();
	if(!m_alienTexture->loadFromFile("Sprites/Space-Invaders-PNG-HD.png"))
	{
		std::cerr << "Error loading alien sprite" << std::endl;
	}
	for(int i = 0; i < m_kNumberOfAliens; i++)
	{
		m_Aliens[i].setSpriteTexture(m_alienTexture);
	}
	resetAliens();
}

//Destructor.
AlienHandler::~AlienHandler()
{
}

//Restarts the timer so the Aliens don't take the entire time since the beginning of the game and add it to their speed.
const void AlienHandler::restartTimer()
{
	m_Timer.m_Time.restart();
}

//When called resets the alien array to original position and state.
const void AlienHandler::resetAliens()
{
	int yPos = 1;
	int xPos = 2;
	for (int i = 0; i < m_kNumberOfAliens; i++)
	{
		m_Aliens[i].m_bDestroyed = false;
		m_Aliens[i].m_Position.x = static_cast<float>((m_Aliens[0].m_kWidth + m_kAlienSpacing) * xPos);
		m_Aliens[i].m_Position.y = static_cast<float>((m_Aliens[0].m_kHeight + m_kAlienSpacing) * yPos);
		if ((i + 1) == (yPos * m_kAliensInLine))
		{
			xPos = 2;
			yPos++;
		}
		else
		{
			xPos++;
		}
	}
	m_iSpeed += m_kSpeedIncrease;
}

//Checks for collisions for all of the aliens in aliens array.
void AlienHandler::collisionDetection(Bullet* bullets)
{
	for (int i = 0; i < m_kNumberOfAliens; i++)
	{
		if (!m_Aliens[i].m_bDestroyed)
		{
			if (m_Aliens[i].collisionDetection(bullets))
			{
				m_Aliens[i].m_bDestroyed = true;
				m_iPoints += 10;

			}
		}
	}
}

//Method checks whether the player has waited enough time before firing again.
const bool AlienHandler::checkCanFire()
{
	if (m_iTimeSinceLastFire < m_kYimeToFire)
	{
		return false;
	}
	else
	{
		m_iTimeSinceLastFire = 0;
		return true;
	}
}

//This method checks whether any of the aliens reached the edge.
const bool AlienHandler::checkForEdge(const int screenWidth)
{
	for (int i = 0; i < m_kNumberOfAliens; i++)
	{
		if (m_Aliens[i].m_Position.x <= 0 || (m_Aliens[i].m_Position.x + m_Aliens[i].m_kWidth) >= screenWidth)
		{
			if (!m_Aliens[i].m_bDestroyed)
			{
				return true;
			}
		}
	}
	return false;
}

//This method moves the aliens in aliens array across the x axis, until it reaches the edge of the screen.
//Then it moves the aliens down once on the y axis and moves in the opposite direction.
const void AlienHandler::moveAliens(const int screenWidth)
{
	if (!checkForEdge(screenWidth))
	{
		for (int i = 0; i < m_kNumberOfAliens; i++)
		{
			if (!m_bMoveLeft)
			{
				m_Aliens[i].move((static_cast<float>(m_iSpeed) * m_Timer.m_fDeltaTime), 0);
			}
			else
			{
				m_Aliens[i].move(-(static_cast<float>(m_iSpeed) * m_Timer.m_fDeltaTime), 0);
			}
		}
	}
	else
	{
		for (int i = 0; i < m_kNumberOfAliens; i++)
		{
			if (m_bMoveLeft)
			{
				m_Aliens[i].move(1.0f, static_cast<float>(m_Aliens[i].m_kHeight));
			}
			else
			{
				m_Aliens[i].move(-1.0f, static_cast<float>(m_Aliens[i].m_kHeight));
			}
		}
		m_bMoveLeft = !(m_bMoveLeft);
	}
}

//main render for AlienHandler.
void AlienHandler::render(sf::RenderWindow& window)
{
	for (int i = 0; i < m_kNumberOfAliens; i++)
	{
		if (!m_Aliens[i].m_bDestroyed)
		{
			m_Aliens[i].render(window);
		}
	}
}

//main update for AlienHandler.
void AlienHandler::update(const int screenWidth)
{
	int numDestroyed = 0;
	m_Timer.m_fDeltaTime = static_cast<float>(m_Timer.m_Time.getElapsedTime().asSeconds());
	moveAliens(screenWidth);
	for (int i = 0; i < m_kNumberOfAliens; i++)
	{
		m_Aliens[i].update();
		if (m_Aliens[i].m_bDestroyed)
		{
			numDestroyed++;
		}
	}
	if (numDestroyed >= m_kNumberOfAliens)
	{
		resetAliens();
	}
	m_Timer.m_Time.restart();
}

//Update for the client in a multi-player game.
void AlienHandler::clientUpdate()
{
	int numDestroyed = 0;
	m_Timer.m_fDeltaTime = static_cast<float>(m_Timer.m_Time.getElapsedTime().asSeconds());
	for (int i = 0; i < m_kNumberOfAliens; i++)
	{
		m_Aliens[i].update();
		if (m_Aliens[i].m_bDestroyed)
		{
			numDestroyed++;
		}
	}
	if (numDestroyed >= m_kNumberOfAliens)
	{
		resetAliens();
	}
	m_Timer.m_Time.restart();
}