#include "GameManager.h"
#include <iostream>
#include <thread>
#include <chrono>


bool gameOver = false;
bool first = true;
bool level_completed = false;
bool first_entrance = true;
bool time_limit = true;
bool ran_out_of_time = false;
bool game_won;

std::string toolbar[MAX_TOOLBAR] = { "LEVEL", "SCORE", "LIVES", "STONES", "TIME" };
std::string messages[MESSAGES] = { "LEVEL COMPLETED!", "GAME OVER!", "YOU'VE WON!", "TIME'S UP!" };
std::string bonuses[BONUSES] = { "More stones to eat!", "Homer goes fast!", "Extra 25 points!"};

enum Data { level, score, lives, stones, sec};
enum Direction {down, right, up, left};
enum monsterDirection {m_up, m_left, m_down, m_right};

GameManager::GameManager()
{
	m_board.openFile();

	m_speed_bonus = 0;
	m_font.loadFromFile("Simp.ttf");

	setToolbar();
	setMessages();
}

void GameManager::runGame(sf::RenderWindow& window)
{
	gameOver = false;
	game_won = false;

	float m_deltaTime;
	float game_time;

	m_audio.playInGameMusic();

	window.clear();
	m_board.loadImages();

	setStartingData();

	while (m_board.loadLevel()) //check if there is next level
	{
		m_board.loadBoard(window, m_dynamic, m_digger); //load file to board
		setBonusesMessages();
		resetSpeedBonus();
		setLevelOnScreen(Board::getLevel());

		game_time = m_game_clock.restart().asSeconds();
		game_time = m_game_clock.getElapsedTime().asSeconds();

		bonus_time - m_bonus_clock.restart().asSeconds();

		setTimeOnScreen(Board::getTime());

		time_limit =((Board::getTime() == -1 )? false : true);
		level_completed = false;

		sf::Event event;

		m_clock.restart();

		while (window.isOpen() && !level_completed)
		{
			draw(window);
			while (window.pollEvent(event))
			{
				switch (event.type)

					case sf::Event::Closed: {
					window.close();
					break;
				}
			}
			m_deltaTime = m_clock.restart().asSeconds();
			moveDigger(m_deltaTime);
			moveMonsters(m_deltaTime);

			checkMoves(window);

			if (time_limit)
				handleTime(window, game_time);

			setData();

			//if diamonds are 0 - next level
			if (Board::getDiamonds() == 0)
			{
				if (m_board.fileEnded())
				{
					game_won = true;
					resetData();
					draw(window);
					m_board.resetFile();
					std::this_thread::sleep_for(std::chrono::seconds(2));
					return;
				}
				else
				{
					Digger::increasePoints(20);
					Board::increaseLevel();
					level_completed = true;
					first = true;
					draw(window);
				}
			}

			if (gameOver) {
				draw(window);
				resetData();
				m_board.resetFile();
				m_audio.gameOver();
				std::this_thread::sleep_for(std::chrono::seconds(2));
				return;
			}

			playSounds();
		}
	}

}

void GameManager::draw(sf::RenderWindow& window)
{
	window.clear();

	m_board.drawBackground(window);

	for (int i = 0; i < MAX_TOOLBAR; i++)
		window.draw(m_toolbar[i]);

	for (int i = 0; i < MAX_TOOLBAR; i++)
		window.draw(m_data[i]);

	m_board.drawStatic(window);

	for (int i = 0; i < m_dynamic.size(); i++)
		m_dynamic[i]->draw(window);


	m_digger->draw(window);


	if (level_completed) {
	    	m_audio.playLevelWon();
			window.draw(m_messages[0]);
			window.display();
			std::this_thread::sleep_for(std::chrono::milliseconds(650));
			return;
	}
	if (gameOver) {
		window.draw(m_messages[1]);
		window.display();
		return;
	}

	//if game won
	if (game_won) {
		m_audio.playGameWon();
		window.draw(m_messages[2]);
		window.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(650));
		return;
	}

	if (ran_out_of_time) {
		//m_audio.playLevelWon();
		window.draw(m_messages[3]);
		window.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(650));
		return;
	}

	//getting time elapsed
	bonus_time = m_bonus_clock.getElapsedTime().asSeconds();

	if (m_digger->gotGift() && bonus_time <= 2) {
		window.draw(m_bonuses[m_digger->getBonusNumber()]);
		window.display();
		return;
	}
	window.display();
}


void GameManager::setToolbar()
{
	for (int i = 0; i < MAX_TOOLBAR; i++)
	{
			m_toolbar[i].setFont(m_font);
			m_toolbar[i].setColor(sf::Color::White);
			m_toolbar[i].setOutlineColor(sf::Color::Black);
			m_toolbar[i].setOutlineThickness(1.0f);
			m_toolbar[i].setString(toolbar[i]);
			m_toolbar[i].setPosition((200.0f * i+ 10.0f), 8);
	}
}

void GameManager::setMessages()
{
	for (int i = 0; i < MESSAGES; i++)
	{
		m_messages[i].setFont(m_font);
		m_messages[i].setColor(sf::Color::White);
		m_messages[i].setOutlineColor(sf::Color::Black);
		m_messages[i].setOutlineThickness(3.0f);
		m_messages[i].setCharacterSize(100);
		m_messages[i].setString(messages[i]);
	}

	m_messages[0].setPosition(75.0f, 300.0f);
	m_messages[1].setPosition(250.0f, 300.0f);
	m_messages[2].setPosition(220.0f, 300.0f);
	m_messages[3].setPosition(280.0f, 300.0f);
}

void GameManager::setBonusesMessages()
{
	for (int i = 0; i < BONUSES; i++)
	{
		m_bonuses[i].setFont(m_font);
		m_bonuses[i].setColor(sf::Color::Yellow);
		m_bonuses[i].setOutlineColor(sf::Color::Black);
		m_bonuses[i].setOutlineThickness(3.0f);
		m_bonuses[i].setCharacterSize(50);
		m_bonuses[i].setString(bonuses[i]);
		m_bonuses[i].setPosition(320.0f, m_board.getTileSize().y + GAP);
	}
}

void GameManager::checkMoves(sf::RenderWindow& window)
{
	for (int i = 0; i < m_dynamic.size(); i++)
		for (int j = 0; j < m_board.getStaticsSize(); j++)
			if (m_dynamic[i]->getGlobalBounds().intersects(m_board.getStaticObject(j)->getGlobalBounds()))
				m_dynamic[i]->collide(*m_board.getStaticObject(j));

	for (int i = 0; i < m_dynamic.size(); i++)
		if (m_digger->getGlobalBounds().intersects(m_dynamic[i]->getGlobalBounds())) {
			m_digger->collide((*m_dynamic[i]));
			m_audio.soundsHit();
			std::this_thread::sleep_for(std::chrono::milliseconds(400));
}

	for (int i = 0; i < m_board.getStaticsSize(); i++)
		if (m_digger->getGlobalBounds().intersects(m_board.getStaticObject(i)->getGlobalBounds())) {
			m_digger->collide(*m_board.getStaticObject(i));
			if (m_board.getStaticObject(i)->isTaken()) {

				if (m_digger->gotDiamond()) {
					m_audio.playDiamond();
					m_digger->resetDiamond();
				}
				else
					m_audio.playEaten();


				//if got gift writing on screen
				if (m_digger->gotGift()){
					bonus_time = m_bonus_clock.restart().asSeconds();
			}
				m_board.deleteStatic(i); 
			}
		}

	bonus_time = m_bonus_clock.getElapsedTime().asSeconds();
	if(bonus_time > 2)
		m_digger->resetGift();

	if (Digger::isDead())
		handleDeath();
}

void GameManager::setStartingData()
{
	//setting the data on top of the screen
	for (int i = 0; i < MAX_TOOLBAR; i++) {

		m_data[i].setFont(m_font);
		m_data[i].setString("test");
		m_data[i].setPosition((m_toolbar[i].getGlobalBounds().width + 25.0f + (200.0f *i)), 8);
		m_data[i].setColor(sf::Color::Black);
	}
}

void GameManager::setData()
{
	setScoreOnScreen();
	setLivesOnScreen(Digger::getLives());
	setStonesOnScreen(Digger::getStones());
}

void GameManager::setLevelOnScreen(int num)
{
		m_data[level].setString(std::to_string(num));
}

void GameManager::setScoreOnScreen()
{
	m_data[score].setString(std::to_string(Digger::getPoints()));
}

void GameManager::setLivesOnScreen(int num)
{
	m_data[lives].setString(std::to_string(num));
}

void GameManager::setStonesOnScreen(int num)
{
	m_data[stones].setString(std::to_string(num));
}

void GameManager::setTimeOnScreen(int num)
{
	m_data[sec].setString(std::to_string(num));
}

void GameManager::resetSpeedBonus()
{
	m_digger->resetSpeed();
	first_entrance = true;
	m_speed_bonus = 0;
}

void GameManager::handleDeath()
{
		if (Digger::getLives() > 0) {

			Digger::decreaseLife();

			for (int i = 0; i < m_dynamic.size(); i++)
				m_dynamic[i]->resetPosition();
			m_digger->resetPosition();


			Digger::revive();
		}
		else
			gameOver = true;

}

void GameManager::handleTime(sf::RenderWindow& window, float game_time)
{
	if (Board::getTime() != -1) {
		game_time = m_game_clock.getElapsedTime().asSeconds();
		if (game_time >= 1) {
			Board::decreaseTime();
			setTimeOnScreen(Board::getTime());
			game_time = m_game_clock.restart().asSeconds();
		}
	}

	//if we reached max time
	if (Board::getTime() == -1) {
		handleDeath();
		Board::setOriginalTime();
		ran_out_of_time = true;
		draw(window);
		ran_out_of_time = false;
		m_audio.playTimesUp();
		std::this_thread::sleep_for(std::chrono::milliseconds(400));
	}
}

void GameManager::resetData()
{
	m_digger->setLivesAgain();
	m_digger->resetPoints();
}

void GameManager::closeFile()
{
	m_board.closeFile();
}

void GameManager::playSounds()
{
	if (Board::getTime() == 30)
		m_audio.playTimeRunningOut();
	if (Board::getTime() == 10)
	m_audio.playLost();
}

void GameManager::moveDigger(float m_deltaTime)
{
	//first itiration speed bonus
	if (m_digger->getSpeed() && first_entrance) {
		m_speed_clock = speedClock.restart().asSeconds();
		m_speed_bonus = 0.025;
		first_entrance = false;
	}

	m_speed_clock = speedClock.getElapsedTime().asSeconds();
	//if speed bonus time elapsed
	if (m_digger->getSpeed() && m_speed_clock >= 4.0) {
		resetSpeedBonus();
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
	{
		m_digger->setAnimation(up, m_digger->getSprite());
		m_digger->setDirection({ 0 , -5 });
		m_digger->move((m_deltaTime * 25.0f) + m_speed_bonus);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
	{
		m_digger->setAnimation(down, m_digger->getSprite());
		m_digger->setDirection({ 0, 5 });
		m_digger->move((m_deltaTime * 25.0f) + m_speed_bonus);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_digger->setAnimation(right, m_digger->getSprite());
		m_digger->setDirection({ 5, 0 });
		m_digger->move((m_deltaTime * 25.0f) + m_speed_bonus);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_digger->setAnimation(left, m_digger->getSprite());
		m_digger->setDirection({ -5, 0 });
		m_digger->move((m_deltaTime * 25.0f) + m_speed_bonus);
	}
}

void GameManager::moveMonsters(float m_deltaTime)
{   
	//setting the direction of the monsters
	if (monsterClock.getElapsedTime().asSeconds() >= 2 || first)
	{
		first = false;
		for (int i = 0; i < m_dynamic.size(); i++)
		{
			m_dynamic[i]->chooseDirection(m_digger->getPosition());
		}
		monsterClock.restart().asSeconds();
	}

	//moving the monsters
	for (int i = 0; i < m_dynamic.size(); ++i)
	{
		if (m_dynamic[i]->getDirection().x == 5)
			m_dynamic[i]->setAnimation(m_right, m_dynamic[i]->getSprite());

		else if (m_dynamic[i]->getDirection().x ==  - 5)
			m_dynamic[i]->setAnimation(m_left, m_dynamic[i]->getSprite());

		else if (m_dynamic[i]->getDirection().y == 5)
			m_dynamic[i]->setAnimation(m_down, m_dynamic[i]->getSprite());

		else if (m_dynamic[i]->getDirection().y == -5)
			m_dynamic[i]->setAnimation(m_up, m_dynamic[i]->getSprite());
		
		m_dynamic[i]->move((m_deltaTime * 20.0f));
	}
}