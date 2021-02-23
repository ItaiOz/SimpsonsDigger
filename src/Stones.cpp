#include "Stones.h"

void Stones::collide(BaseObject& baseObject)
{
	baseObject.collide(*this);
}

void Stones::collide(Demon& demon)
{
	demon.collide(*this);
}

void Stones::collide(Digger& digger)
{
	if (Digger::getStones() > 0)
		setTaken();

	digger.collide(*this);
}

void Stones::collide(Stones& stones)
{
	stones.collide(*this);
}
