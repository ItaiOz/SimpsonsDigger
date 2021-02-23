#pragma once

#include "Demon.h"

class SmartDemon : public Demon
{
public:
	using Demon::Demon;
	virtual void chooseDirection(sf::Vector2f direction);
};
