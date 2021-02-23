#pragma once

#include "Global.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Audio
{
public:
	Audio();

	void soundsHit();
	void playDiamond();
	void playEaten();
	void playLevelWon();
	void playGameWon();
	void playTimeRunningOut();
	void playLost();
	void playInGameMusic();
	void gameOver();
	void playTimesUp(); 

private:
	sf::SoundBuffer buffer[MAX_BUFFER]; //change to const

	sf::Sound m_diamond[3];
	sf::Sound m_hit[MAX_HITS];
	sf::Sound m_finished[3];
	sf::Sound m_eaten[2];
	sf::Sound m_level_won[2];
	sf::Sound m_game_won;
	sf::Sound m_time_running_out;
	sf::Sound m_times_up;
	sf::Sound m_lost;
	sf::Sound m_game_over;
	sf::Music m_in_game;

};
