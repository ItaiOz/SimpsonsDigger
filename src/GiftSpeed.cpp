#include "GiftSpeed.h"

void GiftSpeed::collide(BaseObject& baseObject)
{
	baseObject.collide(*this);
}

void GiftSpeed::collide(Demon& demon)
{
	demon.collide(*this);
}

void GiftSpeed::collide(Digger& digger)
{
	setTaken();
	digger.collide(*this);
}
