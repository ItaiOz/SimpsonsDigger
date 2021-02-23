#include "StaticObject.h"

void StaticObject::setTaken()
{
	m_taken = true;
}

bool StaticObject::isTaken() const
{
	return m_taken;
}
