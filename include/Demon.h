#pragma once

#include "MovingObject.h"

class Demon : public MovingObject
{
public:
	using MovingObject::MovingObject;
	Demon(int row, int col, sf::Vector2f size, sf::Texture* texture);

	virtual void collide(BaseObject& baseObject) override;
	virtual void collide(Demon& demon) override;
	virtual void collide(Digger& digger) override;
	virtual void collide(Diamond& diamond)override;
	virtual void collide(Stones& stones) override;
	virtual void collide(Wall& wall) override;
	virtual void collide(GiftStones& giftstones) override;
	virtual void collide(GiftPoints& giftpoints) override;
	virtual void collide(GiftSpeed& giftspeed) override;

	virtual void setAnimation(int way, sf::Sprite& sprite);

private:

	sf::Clock m_dynamic_clock;
	sf::Vector2i m_source;
	int m_animation_counter = 0;
	int m_animation_frame_duration = 100;
};
