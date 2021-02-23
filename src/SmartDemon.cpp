#include "SmartDemon.h"


void SmartDemon::chooseDirection(sf::Vector2f direction)
{
	float x, y;
	x = direction.x - getPosition().x;
	y = direction.y - getPosition().y;

	if (abs(y) < abs(x))
	{
		if (x < 0) // digger is on right 
		{
			setDirection({ -5, 0 });
		}
		else  // digger is on left
		{
			setDirection({ 5, 0 });
		}
	}
	else 
	{
		if (y < 0) // digger is above
		{
			setDirection({ 0, -5 });
		}
		else // diggerr is below me
		{
			setDirection({ 0, 5 });
		}
	}
}
