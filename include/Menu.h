#pragma once
#include "GameManager.h"
#include "Global.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Menu
{
public:
	Menu();

	bool onMenu(sf::Vector2i mousePos, int &m_index);
	void run();
	void draw();
	void drawAbout();
	void printScreen();
	void setMenu();

private:

	sf::RenderWindow m_window;
	sf::Texture m_texture[MAX_BACKS];
	sf::Texture titleTexture;
	sf::Sprite m_sprite[MAX_BACKS];
	sf::Font m_font;
	sf::Text m_menu[OPTIONS];
	sf::Sprite m_title;
	GameManager Game;

	sf::Clock m_title_clock;
	float m_title_stop_watch;

	int m_index;

	sf::Music music;

};