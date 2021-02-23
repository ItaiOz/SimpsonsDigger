#include "Board.h"
#include <memory>

const char DIGGER = '/';
const char MONSTER = '!';
const char DIAMOND = 'D';
const char STONE = '@';
const char WALL = '#';
const char GIFT = '+';

int Board::m_level = 1;
int Board::m_sec = -1;
int Board::m_originalTime = -1;
int Board::m_diamonds = 0;

std::string images[MAX_IMAGES] = {"homersprite.png", "bobsprite.png", "Diamond.png", "Rock.png", "Wall.png", "Gift.png"};
enum Pics {digger, monster, diamond, stone, wall, gift};

Board::Board()
	:m_cols(0), m_lines(0), m_stones(0), m_indicator(0)
{
}

void Board::loadImages()
{
	m_images.resize(MAX_IMAGES);

	for (int i = 0; i < MAX_IMAGES; i++)
		m_images[i].loadFromFile(images[i]);

	m_texture.loadFromFile("GameBack.jpg");
	m_spriteBack.setTexture(m_texture);
	m_spriteBack.scale((1000 / m_spriteBack.getGlobalBounds().width), (800 / m_spriteBack.getGlobalBounds().height));
}

void Board::deleteStatic(int i)
{
	m_static.erase(m_static.begin() + i);
}
void Board::openFile()
{
	m_boardFile.open("Board.txt");
}

void Board::closeFile()
{
	m_boardFile.close();
}

int Board::getLines() const
{
	return m_lines;
}

int Board::getCols() const
{
	return m_cols;
}

void Board::decreaseStones()
{
	m_stones--;
}

void Board::resetFile()
{
	m_boardFile.clear();
	m_boardFile.seekg(0);
	m_level = 1;
}

void Board::decreaseTime()
{
	m_sec--;
}

void Board::decreaseDiamonds()
{
	m_diamonds--;
}

void Board::increaseLevel()
{
	m_level++;
}

void Board::setOriginalTime()
{
	m_sec = m_originalTime;
}

int Board::getStones() const
{
	return m_stones;
}

int Board::getLevel() 
{
	return m_level;
}

int Board::getDiamonds()
{
	return m_diamonds;
}

int Board::getStaticsSize() const
{
	return (int)m_static.size();
}

int Board::getTime() 
{
	return m_sec;
}

std::unique_ptr<StaticObject>& Board::getStaticObject(int i)
{
	return m_static[i];
}

char Board::getChar(int i, int j) const
{
	return m_vec[i][j];
}

bool Board::loadLevel()
{
	m_vec.clear();
	m_vec_start.clear();

	std::string str;

	if (m_level == 1) {
		m_boardFile >> m_lines;
		m_boardFile >> m_cols;
		m_boardFile >> m_stones;
		m_boardFile >> m_sec;
		m_originalTime = m_sec;
	}

	m_indicator = (int)m_boardFile.tellg();


	if (m_indicator == -1) {
		m_level = 1;
		return false;
	}

	if (m_level != 1)
	{
		std::getline(m_boardFile, str);
		m_boardFile >> m_lines;
		m_boardFile >> m_cols;
		m_boardFile >> m_stones;
		m_boardFile >> m_sec;
		m_originalTime = m_sec;
	}

	Digger::setStones(m_stones);

	std::getline(m_boardFile, str);

	for (int i = 0; i < m_lines; i++) {
		std::getline(m_boardFile, str);
		m_vec.push_back(str);
	}
	m_vec_start = m_vec;

	return true;
}

bool Board::fileEnded()
{
	int i = m_boardFile.tellg();

	return(i == -1);
}

sf::Vector2f Board::getTileSize() const
{
	return m_tile_size;
}

sf::Texture& Board::getTexture(int i)
{
	return m_images[i];
}

void Board::loadBoard(sf::RenderWindow& window, std::vector<std::unique_ptr <MovingObject>>& m_dynamic,
	std::unique_ptr<Digger>& m_digger)
{
	m_static.clear();
	m_dynamic.clear();
	m_digger.reset();

	int chooseGuard;
	char c;
	int gift;

	m_diamonds = 0;

	//for size of every square
	m_tile_size.x = (window.getSize().x / (float)getCols());
	m_tile_size.y =  ((float) window.getSize().y - 50.0f) / (float)getLines();

	for (int i = 0; i < getLines(); i++)
		for (int j = 0; j < getCols(); j++) {
			c = getChar(i, j);

			switch (c)                    
			{
			case DIGGER:
				m_digger = std::make_unique<Digger>(i, j, sf::Vector2f(m_tile_size.x, m_tile_size.y), &getTexture(digger));
				break;

			case MONSTER:
			{
				chooseGuard = rand() % 2; // Randomizes type of guard 

				//	if (chooseGuard) {
				//		m_dynamic.push_back(std::make_unique<SmartDemon>(i, j, m_tile_size, &getTexture(monster)));
			//			std::cout << "monster is " << chooseGuard << std::endl;
			//		}
			//		else{
						m_dynamic.push_back(std::make_unique<RegularDemon>(i, j, m_tile_size, &getTexture(monster)));
				//		std::cout << "monster is " << chooseGuard << std::endl;
				//	}
				break;
			}
			case WALL:
				m_static.push_back(std::make_unique<Wall>(i, j, m_tile_size, &getTexture(wall)));
				break;

			case DIAMOND:
				m_static.push_back(std::make_unique<Diamond>(i, j, m_tile_size, &getTexture(diamond)));
				m_diamonds++;
				break;

			case STONE:
				m_static.push_back(std::make_unique<Stones>(i, j, m_tile_size, &getTexture(stone)));
				break;

			case GIFT: 
				gift = rand() % 3;
				switch (gift)
				{
				case 0:
					m_static.push_back(std::make_unique<GiftStones>(i, j, m_tile_size, &getTexture(5)));
					break;
				case 1:
					m_static.push_back(std::make_unique<GiftPoints>(i, j, m_tile_size, &getTexture(5)));
					break;
				case 2:
					m_static.push_back(std::make_unique<GiftSpeed>(i, j, m_tile_size, &getTexture(5)));
					break;
				}
				break;
			}
			
		}
}

void Board::drawStatic(sf::RenderWindow& window)const
{
		for (int i = 0; i < m_static.size(); i++)
			m_static[i]->draw(window);
		
}

void Board::drawBackground(sf::RenderWindow& window) const
{
	window.draw(m_spriteBack);
}


