#include "Alien.h"

//main render for player.
void Alien::render(sf::RenderWindow& window)
{
	setPosition(m_Position);
	window.draw(*this);
}

//main update for alien.
void Alien::update()
{
	if (!m_bDestroyed)
	{
		setPosition(m_Position.x, m_Position.y);
	}
}

void Alien::move(float speedX, float speedY)
{
	m_Position.x += speedX;
	m_Position.y += speedY;
}

//Checks to see if any of the bullets collided with the alien.
bool Alien::collisionDetection(Bullet* objects)
{
	for (int i = 0; i < m_kNumBullets; i++)
	{
		if (objects[i].getYPos() > -(objects[i].m_kHeight * 1.5f))
		{
			if (objects[i].getXPos() < m_Position.x + m_kWidth && objects[i].getXPos() > m_Position.x)
			{
				if (objects[i].getYPos() < m_Position.y + m_kHeight && objects[i].getYPos() > m_Position.y)
				{
					objects[i].setYPos(-(objects[i].m_kHeight * 1.5f));
					return true;
				}
				else if (objects[i].getYPos() + objects[i].m_kHeight < m_Position.y + m_kHeight && objects[i].getYPos() + objects[i].m_kHeight > m_Position.y)
				{
					objects[i].setYPos(-(objects[i].m_kHeight * 1.5f));
					return true;
				}

			}
			else if (objects[i].getXPos() + objects[i].m_kWidth < m_Position.x + m_kWidth  && objects[i].getXPos() + objects[i].m_kWidth  > m_Position.x)
			{
				if (objects[i].getYPos() < m_Position.y + m_kHeight && objects[i].getYPos() > m_Position.y)
				{
					objects[i].setYPos(-(objects[i].m_kHeight * 1.5f));
					return true;
				}
				else if (objects[i].getYPos() + objects[i].m_kHeight < m_Position.y + m_kHeight && objects[i].getYPos() + objects[i].m_kHeight > m_Position.y)
				{
					objects[i].setYPos(-(objects[i].m_kHeight * 1.5f));
					return true;
				}
			}
		}
	}
	return false;
}

//Constructor.
Alien::Alien()
	:m_bDestroyed(false)
{
	setSize(sf::Vector2f(static_cast<float>(m_kWidth), static_cast<float>(m_kHeight)));
}

//Destructor.
Alien::~Alien()
{
}