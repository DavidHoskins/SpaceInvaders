#include "Player.h"

//main render for player.
void Player::render(sf::RenderWindow& window)
{
	if (isActive() || m_bIsNetworked)
	{
		window.draw(*this);
		setPosition(m_Position);
		for (int i = 0; i < 20; i++)
		{
			m_Bullets[i].setPosition(m_Bullets[i].m_Position);
			if (m_Bullets[i].m_Position.y > 10)
			{
				m_Bullets[i].render(window);
			}
		}
	}
}

//main update for player.
void Player::update(int playerNum)
{
	inputUpdate(playerNum);
	for (int i = 0; i < m_kNumberOfBullets; i++)
	{
		m_Bullets[i].update();
		m_Bullets[i].setYPos(m_Bullets[i].getYPos() - (static_cast<float>(m_kSpeed) * playerController.m_fDeltaTime));
	}
	if (m_bHasFired && playerNum != m_iPlayerNum)
	{
		m_bHasFired = false;
		fireBullet(playerNum);
	}
}

//Checks to see if the axis has been moved from center point.
bool Player::checkAxis(unsigned int joyStick, sf::Joystick::Axis axis)
{
	if (playerController.joyStickAxis(joyStick, axis) > m_kDeadZone || playerController.joyStickAxis(joyStick, axis) < -m_kDeadZone)
	{
		return true;
	}
	return false;
}

//This method handles keyboard inputs.
void Player::keyboardInput()
{
	float movement;
	if (playerController.keyPressed(sf::Keyboard::A))
	{
		movement = m_Position.x - (static_cast<float>(m_kSpeed) * playerController.m_fDeltaTime);
		if (movement > 0.0f)
		{
			m_Position.x = movement;
			m_Position.y = m_Position.y;
		}
	}
	if (playerController.keyPressed(sf::Keyboard::D))
	{
		movement = m_Position.x + (static_cast<float>(m_kSpeed) * playerController.m_fDeltaTime);
		if ((movement + m_kWidth) < 1920.0f)
		{
			m_Position.x = movement;
			m_Position.y = m_Position.y;
		}
	}

	if (checkCanFire() && playerController.keyPressed(sf::Keyboard::Space))
	{
		fireBullet(m_iPlayerNum);
		m_bHasFired = true;
	}
}

//This method handles joystick inputs for all connected joysticks.
//MUST BE COMPATIBLE HARDWARE.
void Player::joystickInput()
{
	if (sf::Joystick::isConnected(1))
	{
		//If the second player isn't active but a controller is connected the second player is activated.
		if (m_iPlayerNum == 2 && !(isActive()))
		{
			setActive(true);
		}
		//This section handles movement.
		if (checkAxis(1, sf::Joystick::X))
		{
			float movement = m_Position.x + ((playerController.joyStickAxis(1, sf::Joystick::X) * m_kControllerSpeed) * playerController.m_fDeltaTime);
			if (movement > 0 && (movement + m_kWidth) < 800)
			{
				m_Position.x = movement;
			}
		}
		if (checkAxis(1, sf::Joystick::Y))
		{
			float movement = m_Position.y + ((playerController.joyStickAxis(1, sf::Joystick::Y) * m_kControllerSpeed) * playerController.m_fDeltaTime);
			if (movement > 0 && (movement + m_kWidth) < 800)
			{
				m_Position.y = movement;
			}
		}

		//This section handles abilities.
		if (checkCanFire() && playerController.joyStickButtonPressed(1, m_kFireButNum))
		{
			fireBullet(2);
			m_bHasFired = true;
		}
	}
	else
	{
		//If the controller is disconnected the second player is freed up again.
		if (m_iPlayerNum == 2 && (isActive()))
		{
			setActive(false);
		}
	}
}

//Fires a bullet by using the next position in the bullet array and moving that to the players position.
void Player::fireBullet(int playerNum)
{
	m_Bullets[m_iFirePosition].setXPos((m_Position.x + ((m_kWidth / 2) - (m_Bullets[m_iFirePosition].m_kWidth / 2))));
	m_Bullets[m_iFirePosition].setYPos((m_Position.y - 40));
	if (m_iFirePosition < 19)
	{
		m_iFirePosition++;
	}
	else
	{
		m_iFirePosition = 0;
	}
}

//Player controls.
void Player::inputUpdate(int playerNum)
{
	if (m_iPlayerNum == playerNum)
	{
		keyboardInput();
	}
	else
	{
		joystickInput();
	}
	playerController.m_fDeltaTime = playerController.m_Time.restart().asSeconds();

	setPosition(m_Position.x, m_Position.y);
}

//Collision detection with the player.
void Player::collisionDetection(Alien* aliens)
{
	for (int i = 0; i < 20; i++)
	{
		if (aliens[i].m_bDestroyed == false)
		{
			if (aliens[i].getYPos() < 0)
			{
				m_iLivesLeft = 0;
			}

			if (aliens[i].getXPos() < m_Position.x + m_kWidth && aliens[i].getXPos() > m_Position.x)
			{
				if (aliens[i].getYPos() < m_Position.y + m_kHeight && aliens[i].getYPos() > m_Position.y)
				{
					m_iLivesLeft--;
					m_Position = sf::Vector2f(400.0f, (800.0f - (m_kHeight * 1.5f)));
				}
				else if (aliens[i].getYPos() + aliens[i].m_kHeight < m_Position.y + m_kHeight && aliens[i].getYPos() + aliens[i].m_kHeight > m_Position.y)
				{
					m_iLivesLeft--;
					m_Position = sf::Vector2f(400.0f, (800.0f - (m_kHeight * 1.5f)));
				}

			}
			else if (aliens[i].getXPos() + aliens[i].m_kWidth < m_Position.x + m_kWidth && aliens[i].getXPos() + aliens[i].m_kWidth  > m_Position.x)
			{
				if (aliens[i].getYPos() < m_Position.y + m_kHeight && aliens[i].getYPos() > m_Position.y)
				{
					m_iLivesLeft--;
					m_Position = sf::Vector2f(400.0f, (800.0f - (m_kHeight * 1.5f)));
				}
				else if (aliens[i].getYPos() + aliens[i].m_kHeight < m_Position.y + m_kHeight && aliens[i].getYPos() + aliens[i].m_kHeight > m_Position.y)
				{
					m_iLivesLeft--;
					m_Position = sf::Vector2f(400.0f, (800.0f - (m_kHeight * 1.5f)));

				}
			}
		}
	}
}

//Method checks whether the player has waited enough time before firing again.
bool Player::checkCanFire()
{
	if (!(playerController.joyStickButtonPressed(1, m_kFireButNum)) && !(playerController.keyPressed(sf::Keyboard::Space)))
	{
		m_bReleasedKey = true;
		return false;
	}
	else
	{
		if (m_bReleasedKey)
		{
			m_bReleasedKey = false;
			return true;
		}
		else
		{
			return false;
		}
	}
}

//Constructor.
Player::Player()
	:m_iFirePosition(0)
	,m_fTimeSinceLastFire(0.1f)
	,m_bIsNetworked(false)
{
	m_Position.x = 420;
	m_Position.y = 700;
	setSize(sf::Vector2f(static_cast<float>(m_kWidth), static_cast<float>(m_kHeight)));
	setFillColor(sf::Color::Red);
}

//Destructor.
Player::~Player()
{
}