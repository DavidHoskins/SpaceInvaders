#include "Bullet.h"

//main render for Bullet.
void Bullet::render(sf::RenderWindow& window)
{
	window.draw(*this);
}

//main update for Bullet.
void Bullet::update()
{
	setPosition(m_Position.x, m_Position.y);

}

Bullet::Bullet()
{
	setSize(sf::Vector2f(static_cast<float>(m_kWidth), static_cast<float>(m_kHeight)));
	setPosition(sf::Vector2f(100.0f, 100.0f));
}

Bullet::~Bullet()
{

}