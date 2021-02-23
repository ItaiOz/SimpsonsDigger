#pragma once

#include "BaseObject.h"
#include "Global.h"

class MovingObject : public BaseObject
{
public:
	using BaseObject::BaseObject;
	MovingObject(int row, int col, sf::Vector2f size, sf::Texture* texture);
	void move(float delta);
	virtual void chooseDirection(sf::Vector2f direction) = 0;
	void setDirection(sf::Vector2f direction);
	void changeDirection();
	void resetPosition();
	virtual void setAnimation(int way, sf::Sprite& sprite) = 0;

	sf::Vector2f getDirection()const;
	sf::Vector2f getStart();

private:

	sf::Vector2f m_direction;
	sf::Vector2f m_starting_position;
	float m_lastDelta;

};
