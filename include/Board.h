#pragma once

#include <SFML/Graphics.hpp>
#include "BaseObject.h"
#include "MovingObject.h"
#include "StaticObject.h"
#include "SmartDemon.h"
#include "RegularDemon.h"
#include "Wall.h"
#include "Stones.h"
#include "Gift.h"
#include "GiftSpeed.h"
#include "GiftStones.h"
#include "GiftPoints.h"
#include "Demon.h"
#include "Diamond.h"
#include "Digger.h"
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>


class Board
{
public:
	Board();
	void loadBoard(sf::RenderWindow& window, std::vector<std::unique_ptr <MovingObject>>& m_dynamic,
		std::unique_ptr<Digger>& m_digger);
	void drawStatic(sf::RenderWindow& window)const;
	void drawBackground(sf::RenderWindow& window)const;
	//-------------------------------------------
	sf::Texture& getTexture(int i);
	sf::Vector2f getTileSize() const;

	//change to board only
	std::unique_ptr<StaticObject>& getStaticObject(int i);

	void openFile();
	void closeFile();
	void loadImages();
	void deleteStatic(int i);
	void decreaseStones();
	void resetFile();
	//remove the static
	static void decreaseTime();
	static void decreaseDiamonds();
	static void increaseLevel();
	static void setOriginalTime();
	bool loadLevel();
	bool fileEnded();

	int getLines()const;
	int getCols()const;
	int getStaticsSize()const;
	int getStones()const;
	static int getTime();
	static int getLevel();
	static int getDiamonds();


	char getChar(int i, int j)const;
	//std::vector<std::unique_ptr <StaticObject>>& getStaticVector();

private:
	std::vector<std::unique_ptr <StaticObject>> m_static;
	//----------------------------------------
	std::vector<sf::Texture> m_images;
	sf::Texture m_texture;
	sf::Sprite m_spriteBack;
	std::ifstream m_boardFile;

	std::vector<std::string> m_vec;
	std::vector<std::string> m_vec_start;

	sf::Vector2f m_tile_size;
	static int m_level;
	static int m_sec;
	static int m_originalTime;
	static int m_diamonds;
	int m_indicator;
	int m_lines;
	int m_cols;
	int m_stones;
	
};