#include "MovingObject.h"

MovingObject::MovingObject(int row, int col, sf::Vector2f size, sf::Texture* texture)
	:BaseObject(row, col, size, texture)
{
	m_lastDelta = 0;
	m_starting_position.x = getPosition().x;
	m_starting_position.y = getPosition().y + GAP;

}

void MovingObject::move(float delta)
{
	getSprite().move(m_direction * delta);
	m_lastDelta = delta;
	getPosition() = getSprite().getPosition();
}

void MovingObject::setDirection(sf::Vector2f direction)
{
	m_direction = direction;
}

void MovingObject::changeDirection()
{
	getSprite().move(-m_direction * m_lastDelta);


}

void MovingObject::resetPosition()
{
	getSprite().setPosition(m_starting_position);
	getPosition() = m_starting_position;
}

sf::Vector2f MovingObject::getDirection() const
{
	return m_direction;
}

sf::Vector2f MovingObject::getStart()
{
	return m_starting_position;
}