#include "Digger.h"
#include <iostream>
#include <thread>
#include <chrono>

int Digger::m_allowedStones = 0;
int Digger::m_points = 0;
int Digger::m_lives = 3;
bool Digger::is_dead = false;


Digger::Digger(int row, int col, sf::Vector2f size, sf::Texture* texture)
	:MovingObject(row, col, size, texture)
{
	getSprite().setTextureRect(sf::IntRect(0, 35, 22, 35));
	getSprite().setScale(size.x * 0.022, size.y * 0.022);

	m_bonus_number = 0;
}

void Digger::setStones(int num)
{
	m_allowedStones = num;
}

void Digger::increaseStones(int num)
{
	m_allowedStones += num;
}

int Digger::getStones() 
{
	return m_allowedStones;
}

int Digger::getLives()
{
	return m_lives;
}

int Digger::getPoints()
{
	return m_points;
}

void Digger::setLivesAgain()
{
	m_lives = 3;
}

void Digger::decreaseLife()
{
	m_lives--;
}

void Digger::increasePoints(int num)
{
	m_points += num;
}

void Digger::revive()
{
	is_dead = false;
}

bool Digger::isDead()
{
	return is_dead;
}

void Digger::resetPoints()
{
	m_points = 0;
}

bool Digger::getSpeed() const
{
	return m_speed;
}

void Digger::resetSpeed()
{
	m_speed = false;
}

bool Digger::gotGift() const
{
	return got_gift;
}

bool Digger::gotDiamond() const
{
	return got_diamond;
}

void Digger::resetDiamond()
{
	got_diamond = false;
}

void Digger::resetGift()
{
	got_gift = false;
}

int Digger::getBonusNumber() const
{
	return m_bonus_number;
}

void Digger::chooseDirection(sf::Vector2f direction)
{
	setDirection(direction);
}

void Digger::collide(BaseObject& baseObject)
{
	baseObject.collide(*this);
}

void Digger::collide(Demon& demon)
{
	is_dead = true;
}

void Digger::collide(Digger& digger)
{
}

void Digger::collide(Diamond& diamond)
{
	got_diamond = true;
	increasePoints(15);
}

void Digger::collide(Stones& stones)
{
	if (m_allowedStones == 0) {
		std::this_thread::sleep_for(std::chrono::milliseconds(400));
		is_dead = true;
	}
	else if (m_allowedStones > 0)
		m_allowedStones--;
}

void Digger::collide(Wall& wall)
{
	changeDirection();
}

void Digger::collide(GiftStones& giftstones)
{
	m_bonus_number = 0;
	got_gift = true;
    increaseStones(3);
}

void Digger::collide(GiftPoints& giftpoints)
{
	m_bonus_number = 2;
	got_gift = true;
	increasePoints(25);
}

void Digger::collide(GiftSpeed& giftspeed)
{
	m_bonus_number = 1;
	got_gift = true;
	m_speed = true;
}

void Digger::setAnimation(int way, sf::Sprite& sprite)
{
	m_source.y = way;
	m_animation_counter += m_dynamic_clock.restart().asMilliseconds();


	if ((m_animation_counter >= m_animation_frame_duration))
	{

		m_animation_counter -= m_animation_frame_duration;
		m_source.x++;
	}

	if (m_source.x * 22 >= 22 * 3)
		m_source.x = 0;

	sprite.setTextureRect(sf::IntRect(m_source.x * 22, m_source.y * 35, 22, 35));

}