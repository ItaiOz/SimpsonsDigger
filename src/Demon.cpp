#include "Demon.h"

#include "Wall.h"
#include "Digger.h"
#include "Diamond.h"
#include "Stones.h"
#include "GiftSpeed.h"
#include "GiftPoints.h"
#include "GiftStones.h"

Demon::Demon(int row, int col, sf::Vector2f size, sf::Texture* texture)
	:MovingObject(row, col, size, texture)
{
	getSprite().setTextureRect(sf::IntRect(80, 0, 120, 45));
	getSprite().setScale(size.x * 0.010, size.y * 0.010);
}

void Demon::collide(BaseObject& baseObject)
{
	baseObject.collide(*this);
}

void Demon::collide(Demon& demon)
{
	changeDirection();
}

 void Demon::collide(Digger& digger)
{
	digger.collide(*this);
}

void Demon::collide(Diamond& diamond)
{
	changeDirection();
}

void Demon::collide(Stones& stones)
{
	changeDirection();
}

void Demon::collide(Wall& wall)
{
	changeDirection();
}

void Demon::collide(GiftStones& giftstones)
{
}

void Demon::collide(GiftPoints& giftpoints)
{
}

void Demon::collide(GiftSpeed& giftspeed)
{
}

void Demon::setAnimation(int way, sf::Sprite& sprite)
{
	m_source.x = way;
	m_animation_counter += m_dynamic_clock.restart().asMilliseconds();


	if ((m_animation_counter >= m_animation_frame_duration))
	{

		m_animation_counter -= m_animation_frame_duration;
		m_source.y++;
	}

	if (m_source.y * 60 >= 60 * 3)
		m_source.y = 0;

	sprite.setTextureRect(sf::IntRect(m_source.x * 40, m_source.y * 60, 40, 60));

}