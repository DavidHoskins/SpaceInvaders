#ifndef ALIEN_H
#define ALIEN_H

#include "GameObject.h"
#include "Bullet.h"

class Alien : public GameObject
{
public:
	virtual void render(sf::RenderWindow& window);
	virtual void update();

	Alien();
	~Alien();

	const int m_kWidth = 125;
	const int m_kHeight = 100;

	const int m_kNumBullets = 20;

	bool collisionDetection(Bullet* objects);

	void move(float speedX, float speedY);

	float getXPos(){return m_Position.x;}
	float getYPos(){return m_Position.y;}

	bool m_bDestroyed;

	void setSpriteTexture(sf::Texture* alienTexture);
private:
	sf::Sprite* m_alienSprite;

};

#endif //!ALIEN_H
