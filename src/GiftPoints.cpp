#include "GiftPoints.h"

void GiftPoints::collide(BaseObject& baseObject)
{
	baseObject.collide(*this);
}

void GiftPoints::collide(Demon& demon)
{
	demon.collide(*this);
}

void GiftPoints::collide(Digger& digger)
{
	setTaken();
	digger.collide(*this);
}
