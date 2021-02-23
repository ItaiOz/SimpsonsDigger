#include "RegularDemon.h"
#include "Time.h"

void RegularDemon::chooseDirection(sf::Vector2f direction)
{
	 //srand(time(NULL));
	int i = rand()% 4;
	if (i == m_lastDirection)
		i =  ((i + 2)% 4);
	m_lastDirection = i;
	
	switch (i)
	{
	case 0: {
		setDirection({ 5, 0 });
		break;
	}
	case 1: {
		setDirection({ -5, 0 });
		break;
	}
	case 2: {
		setDirection({ 0, 5 });
		break;
	}
	case 3:{
		setDirection({ 0, -5 });
		break;
	}
	}
}
