#pragma once

#include "StaticObject.h"
#include "Demon.h"
#include "Digger.h"

class Stones : public StaticObject
{
public:
	using StaticObject::StaticObject;

	virtual void collide(BaseObject& BaseObject) override;
	virtual void collide(Demon& Demon) override;
	virtual void collide(Digger& Digger) override;
	virtual void collide(Diamond& Diamond)override {};
	virtual void collide(Stones& stones) override;
	virtual void collide(Wall& Wall) override {};
	virtual void collide(GiftStones& giftstones) override {};
	virtual void collide(GiftPoints& giftpoints) override {};
	virtual void collide(GiftSpeed& giftspeed) override {};

};
