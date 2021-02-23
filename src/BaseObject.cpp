#include "BaseObject.h"

BaseObject::BaseObject(int row, int col, sf::Vector2f size, sf::Texture* texture)
	:m_position((float)col* size.x, (float)row* size.y), m_size(size), m_sprite(*texture)
{
	m_sprite.setPosition(m_position.x,(m_position.y + GAP));
	m_sprite.scale((m_size.x) / m_sprite.getGlobalBounds().width, (m_size.y / m_sprite.getGlobalBounds().height));
}


void BaseObject::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

sf::Vector2f BaseObject::getPosition() const
{
	return m_position;
}

sf::FloatRect BaseObject::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::Sprite& BaseObject::getSprite()
{
	return m_sprite;
}

sf::Vector2f BaseObject::getSize()
{
	return m_size;
}

