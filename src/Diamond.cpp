#include "Diamond.h"

void Diamond::collide(BaseObject& baseObject)
{
	baseObject.collide(*this);
}

void Diamond::collide(Demon& demon)
{
	demon.collide(*this);
}

void Diamond::collide(Digger& digger)
{
	setTaken();
	Board::decreaseDiamonds();
	digger.collide(*this);
}