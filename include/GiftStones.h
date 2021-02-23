#pragma once

#include "Gift.h"
#include "Demon.h"
#include "Digger.h"

class GiftStones :public Gift
{
	using Gift::Gift;

	virtual void collide(BaseObject& baseObject) override;
	virtual void collide(Demon& demon) override;
	virtual void collide(Digger& digger) override;
	virtual void collide(Diamond& diamond)override {};
	virtual void collide(Stones& stones) override {};
	virtual void collide(Wall& wall) override {};
	virtual void collide(GiftStones& giftstones) override {};
	virtual void collide(GiftPoints& giftpoints) override {};
	virtual void collide(GiftSpeed& giftspeed) override {};

};