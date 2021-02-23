#include "GiftStones.h"

void GiftStones::collide(BaseObject& baseObject)
{
	baseObject.collide(*this);
}

void GiftStones::collide(Demon& demon)
{
	demon.collide(*this);
}

void GiftStones::collide(Digger& digger)
{
	setTaken();
	digger.collide(*this);
}
