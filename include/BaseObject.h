#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Global.h"

class Wall;
class Demon;
class Digger;
class Diamond;
class Stones;
class GiftStones;
class GiftSpeed;
class GiftPoints;

class BaseObject
{
public:
	BaseObject() = default;
	BaseObject(int row, int col, sf::Vector2f size, sf::Texture * texture);
	virtual ~BaseObject() = default;

	virtual void collide(BaseObject& baseObject) = 0;
	virtual void collide(Demon& demon) = 0;
	virtual void collide(Digger& digger) = 0;
	virtual void collide(Diamond& diamond) = 0;
	virtual void collide(Stones& stones) = 0;
	virtual void collide(Wall& wall) = 0;
	virtual void collide(GiftStones& giftstones) = 0;
	virtual void collide(GiftPoints& giftpoints) = 0;
	virtual void collide(GiftSpeed& giftspeed) = 0;

    virtual void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition()const;
	sf::FloatRect getGlobalBounds()const;
	sf::Sprite& getSprite();
	sf::Vector2f getSize();

private:
	sf::Vector2f m_position;
	sf::Sprite m_sprite;
	sf::Vector2f m_size;

};

