#pragma once

#include "MovingObject.h"
#include "Global.h"

class Digger : public MovingObject
{
public:
	
	using MovingObject :: MovingObject;
	Digger(int row, int col, sf::Vector2f size, sf::Texture* texture);
	void increaseStones(int num);
	static void setStones(int num);
	static int getStones();
	static int getLives();
	static int getPoints();
	static void setLivesAgain();
	static void decreaseLife();
	static void increasePoints(int num);
	static void revive();
	static bool isDead();
	static void resetPoints();
	bool getSpeed() const;
	bool gotGift() const;
	bool gotDiamond() const;
	void resetDiamond();
	void resetSpeed();
	void resetGift();
	int getBonusNumber() const;
	virtual void chooseDirection(sf::Vector2f direction);
	virtual void setAnimation(int way, sf::Sprite& sprite);

	virtual void collide(BaseObject& baseObject) override;
	virtual void collide(Demon& demon) override;
	virtual void collide(Digger& digger) override;
	virtual void collide(Diamond& diamond)override;
	virtual void collide(Stones& stones) override;
	virtual void collide(Wall& wall) override;
	virtual void collide(GiftStones& giftstones) override;
	virtual void collide(GiftPoints& giftpoints) override;
	virtual void collide(GiftSpeed& giftspeed) override;


private:

	bool m_speed = false;

	int m_bonus_number;
	static int m_allowedStones;
	static int m_lives;
	static int m_points;
	static bool is_dead;
	bool got_gift = false;
	bool got_diamond = false;

	//move to moving object class
	sf::Clock m_dynamic_clock;
	sf::Vector2i m_source;
	int m_animation_counter = 0;
	int m_animation_frame_duration = 100;

};
