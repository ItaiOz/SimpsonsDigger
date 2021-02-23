#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Board.h"
#include "Digger.h"
#include "Global.h"
#include "Audio.h"

class GameManager
{
public:
	GameManager();

	void runGame(sf::RenderWindow &window);
	void draw(sf::RenderWindow& window);
	void setToolbar();
	void checkMoves(sf::RenderWindow& window);
	void setStartingData();
	void setMessages();
	void setBonusesMessages();
	void setData();
	void setLevelOnScreen(int num);
	void setScoreOnScreen();
	void setLivesOnScreen(int num);
	void setStonesOnScreen(int num);
	void setTimeOnScreen(int num);
	void resetSpeedBonus();
	void handleDeath();
	void handleTime(sf::RenderWindow& window, float game_time);
	void resetData();
	void closeFile();
	void playSounds();

private:

	void moveDigger(float m_deltaTime);
	void moveMonsters(float m_deltaTime);

	Audio m_audio;

	//insert to vector
	sf::Clock m_game_clock;
	sf::Clock speedClock;
	sf::Clock monsterClock;
	sf::Clock m_clock;
	sf::Clock m_bonus_clock;

	sf::Texture m_texture;
	sf::Sprite m_sprite[MAX_SPRITES];

	sf::Font m_font;

	sf::Text m_toolbar[MAX_TOOLBAR];
	sf::Text m_messages[MESSAGES];
	sf::Text m_bonuses[BONUSES];
	sf::Text m_data[MAX_TOOLBAR];

	std::vector<std::unique_ptr <MovingObject>> m_dynamic;
	std::unique_ptr<Digger> m_digger;

	Board m_board;

	//try to save on variables

	float m_speed_bonus;
	float m_speed_clock;
	int bonus_time;
};
