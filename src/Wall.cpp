#include "Wall.h"
#include "Demon.h"
#include "Digger.h"

void Wall::collide(BaseObject& baseObject)
{
	baseObject.collide(*this);
}

void Wall::collide(Demon& demon)
{
	demon.collide(*this);
}

void Wall::collide(Digger& digger)
{

	digger.collide(*this);
}
