#ifndef BULLET_H
#define BULLET_H
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet();

	//Update methods.
	virtual void render(sf::RenderWindow& window);
	virtual void update();

	const int m_kWidth = 10;
	const int m_kHeight = 20;

	void setXPos(float val){m_Position.x = val;}
	void setYPos(float val){m_Position.y = val;}
	float getYPos(){return m_Position.y;}
	float getXPos(){return m_Position.x;}

private:

};

#endif //!BULLET_H
