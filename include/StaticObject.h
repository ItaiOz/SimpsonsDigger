#pragma once

#include "BaseObject.h"
#include <SFML/Graphics.hpp>

class StaticObject : public BaseObject
{
public:
	using BaseObject::BaseObject;

	void setTaken();
	bool isTaken()const;

private:
	bool m_taken = false;
};