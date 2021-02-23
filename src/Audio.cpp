#include "Audio.h"

Audio::Audio()
{
	buffer[0].loadFromFile("d'oh.wav");
	buffer[1].loadFromFile("doh1.wav");
	buffer[2].loadFromFile("doh2.wav");
	buffer[3].loadFromFile("doh3.wav");
	buffer[4].loadFromFile("donut.wav");
	buffer[5].loadFromFile("woohoo.wav");
	buffer[6].loadFromFile("woohoo2.wav");
	buffer[7].loadFromFile("levelwin.wav");
	buffer[8].loadFromFile("gamewin.wav");
	buffer[9].loadFromFile("timesup.wav");
	buffer[10].loadFromFile("What Am I Gonna Do.wav");
	buffer[11].loadFromFile("suckers.wav");
	buffer[12].loadFromFile("ahhh.wav");
	buffer[13].loadFromFile("crap.wav");
	buffer[14].loadFromFile("donut2.wav");
	buffer[15].loadFromFile("donut3.wav");
	m_in_game.openFromFile("ingamemusic.ogg");


	m_hit[0].setBuffer(buffer[0]);
	m_hit[1].setBuffer(buffer[1]);
	m_hit[2].setBuffer(buffer[2]);
	m_hit[3].setBuffer(buffer[3]);

	m_diamond[0].setBuffer(buffer[4]);
	m_diamond[1].setBuffer(buffer[14]);
	m_diamond[2].setBuffer(buffer[15]);

	m_eaten[0].setBuffer(buffer[5]);
	m_eaten[1].setBuffer(buffer[6]);

	m_level_won[0].setBuffer(buffer[7]);
	m_level_won[1].setBuffer(buffer[11]);
	m_game_won.setBuffer(buffer[8]);
	m_times_up.setBuffer(buffer[13]);
	m_lost.setBuffer(buffer[10]);
	m_game_over.setBuffer(buffer[12]);
	m_time_running_out.setBuffer(buffer[9]);
}

void Audio::soundsHit()
{
	int i = rand() % 4;

	if (i == 0) 
		m_hit[0].play();
	
	else if (i == 1) 
		m_hit[1].play();
	

	else if (i == 2)
		m_hit[2].play();
	
	else
		m_hit[3].play();
	
}

void Audio::playDiamond()
{
	int i = rand() % 6;

	if (i == 0)
		m_diamond[0].play();

	else if (i == 1)
		m_diamond[1].play();

	else if (i == 2)
		m_diamond[2].play();

	else
		m_eaten[1].play();

}

void Audio::playEaten()
{
	int i = rand() % 3;

	if (i == 0)
		m_eaten[0].play();

	else if (i == 1)
		m_eaten[1].play();
}

void Audio::playLevelWon()
{
	m_diamond[0].pause();
	m_diamond[1].pause();
	for (int i = 0; i < 2; i++)
		m_eaten[i].pause();

	int i = rand() % 2;

	if(i == 0)
	m_level_won[0].play();
	else
	m_level_won[1].play();
}

void Audio::playGameWon()
{
	m_in_game.stop();
	m_diamond[0].pause();
	m_diamond[1].pause();
	for (int i = 0; i < 2; i++)
		m_eaten[i].stop();

	m_game_won.play();
}

void Audio::playTimeRunningOut()
{
	m_time_running_out.play();
}

void Audio::playLost()
{
	m_lost.play();
}

void Audio::playInGameMusic()
{
	m_in_game.play();
	m_in_game.setVolume(100);
	m_in_game.setLoop(true);
}

void Audio::gameOver()
{
	for (int i = 0; i < MAX_HITS; i++)
		m_hit[i].stop();

	m_in_game.stop();
	m_game_over.play();
}

void Audio::playTimesUp()
{
	m_times_up.play();
}
