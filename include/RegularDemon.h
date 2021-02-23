#pragma once

#include "Demon.h"

class RegularDemon : public Demon
{
public:
	using Demon::Demon;
	

	virtual void chooseDirection(sf::Vector2f direction);
private:
	int m_lastDirection = 0 ;
};
