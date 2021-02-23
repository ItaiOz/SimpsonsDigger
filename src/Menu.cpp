#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

std::string options[OPTIONS] = { "PLAY", "ABOUT", "X", "Digger\nVersion!" };


Menu::Menu()
	:m_window(sf::VideoMode(1000, 800), "SipmsonsDigger", sf::Style::Close)

{
	m_texture[0].loadFromFile("Opening.jpg");
	m_sprite[0].setTexture(m_texture[0]);
	m_sprite[0].setPosition(0, 0);
	m_index = 0;

	m_font.loadFromFile("Simp.ttf");

	m_texture[1].loadFromFile("GameBack2.png");
	m_sprite[1].setTexture(m_texture[1]);
	m_sprite[1].setPosition(0, 0);
	m_sprite[1].scale(1000 / m_sprite[1].getGlobalBounds().width, 800 / m_sprite[1].getGlobalBounds().height);

	music.openFromFile("The Simpsons.ogg");

	titleTexture.loadFromFile("scale.png");

	setMenu();
}

bool Menu::onMenu(sf::Vector2i mousePos, int& m_index)
{
	for (m_index = 0; m_index < OPTIONS - 1; m_index++)
		if (((float)mousePos.x > m_menu[m_index].getGlobalBounds().left &&
			(float)mousePos.x < m_menu[m_index].getGlobalBounds().left + m_menu[m_index].getGlobalBounds().width)
			&& ((float)mousePos.y > m_menu[m_index].getGlobalBounds().top &&
			(float)mousePos.y < m_menu[m_index].getGlobalBounds().top + m_menu[m_index].getGlobalBounds().height))
			return true;

	return false;
}

void Menu::run()
{


	m_title_stop_watch = m_title_clock.restart().asMilliseconds();
	music.play();

	while (m_window.isOpen())
	{


		sf::Event event;


		while (m_window.pollEvent(event))
		{


			switch (event.type)
			{

			case sf::Event::Closed:
				m_window.close();
				break;

			case sf::Event::MouseMoved:
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

				if (onMenu(mousePos, m_index))
					m_menu[m_index].setColor(sf::Color::Yellow);

				else
					for (int i = 0; i < OPTIONS; i++)
						m_menu[i].setColor(sf::Color::White);

				printScreen();
				break;
			}

			case sf::Event::MouseButtonReleased:
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
				if (onMenu(mousePos, m_index))
				{
					switch (m_index)
					{
					case 0:
						music.stop();
						Game.runGame(m_window);
						music.play();
						break;
					case 1:
						drawAbout();
						break;
					case 2:
						Game.closeFile();
						m_window.close();
						break;
					}
				}
			}


			}
		}
	}
}

void Menu::draw()
{
	m_window.draw(m_sprite[0]);
	for (int i = 0; i < OPTIONS; i++)
		m_window.draw(m_menu[i]);
	m_window.draw(m_title);
}

void Menu::drawAbout()
{
	sf::Event event;

	while (m_window.isOpen())
	{
	

		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{

			case sf::Event::Closed:
				m_window.close();
				break;



			case sf::Event::MouseMoved:
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

				if (((float)mousePos.x > m_menu[2].getGlobalBounds().left &&
					(float)mousePos.x < m_menu[2].getGlobalBounds().left + m_menu[2].getGlobalBounds().width)
					&& ((float)mousePos.y > m_menu[2].getGlobalBounds().top &&
					(float)mousePos.y < m_menu[2].getGlobalBounds().top + m_menu[2].getGlobalBounds().height)) {
					m_menu[2].setColor(sf::Color::Yellow);
				//	break;
				}
				else
					m_menu[2].setColor(sf::Color::White);

				m_window.clear();
				m_window.draw(m_sprite[1]);
				m_window.draw(m_menu[2]);
				m_window.display();
				break;
			}

			case sf::Event::MouseButtonReleased:
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

				if (((float)mousePos.x > m_menu[2].getGlobalBounds().left &&
					(float)mousePos.x < m_menu[2].getGlobalBounds().left + m_menu[2].getGlobalBounds().width)
					&& ((float)mousePos.y > m_menu[2].getGlobalBounds().top &&
					(float)mousePos.y < m_menu[2].getGlobalBounds().top + m_menu[2].getGlobalBounds().height))
					return;
				
			}
			}
		}
	}
}

void Menu::printScreen()
{
	m_window.clear();
	draw();
	m_window.display();
}

void Menu::setMenu()
{

	m_title.setTexture(titleTexture);
	m_title.setPosition(372, 30);
	m_title.setScale(0.2, 0.2);


	for (int i = 0; i < OPTIONS - 1; i++)
	{
		m_menu[i].setFont(m_font);
		m_menu[i].setColor(sf::Color::White);
		m_menu[i].setOutlineColor(sf::Color::Black);
		m_menu[i].setOutlineThickness(3.0f);
		m_menu[i].setString(options[i]);
		m_menu[i].setCharacterSize(50);
		if(i !=2)
		m_menu[i].setPosition(100.0f, (200.0f * (i + 1)) + 50.0f);
		else
			m_menu[i].setPosition(925.0f, 20.0f);
	}

	m_menu[3].setFont(m_font);
	m_menu[3].setFillColor(sf::Color::Red); 
	m_menu[3].setOutlineColor(sf::Color::Black);
	m_menu[3].setOutlineThickness(3.0f);
	m_menu[3].setString(options[3]);
	m_menu[3].setCharacterSize(50);
	m_menu[3].setPosition(420.0f, 133.0f);
	m_menu[3].setRotation(-5);
}