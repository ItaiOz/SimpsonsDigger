#pragma once

#include "StaticObject.h"

class Gift :public StaticObject
{
	using StaticObject::StaticObject;

	virtual void collide(BaseObject& baseObject) = 0;
	virtual void collide(Demon& demon) = 0 ;
	virtual void collide(Digger& digger) = 0;
	virtual void collide(Diamond& diamond) = 0;
	virtual void collide(Stones& stones) = 0;
	virtual void collide(Wall& wall) = 0;
	virtual void collide(GiftStones& giftstones) = 0;
	virtual void collide(GiftPoints& giftpoints) = 0;
	virtual void collide(GiftSpeed& giftspeed) = 0;

};