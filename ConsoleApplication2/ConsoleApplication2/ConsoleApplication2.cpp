#include "stdafx.h"
#include"Board.h"
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Export.hpp>
#include <SFML\Graphics\Texture.hpp>
#include<SFML\Audio.hpp>
#include<SFML\Audio\Sound.hpp>
#include<SFML\Audio\SoundBuffer.hpp>
#include<string>
#include<vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include"button.h"
#include"TextField.h"

using namespace std;
using namespace sf;	

template <class T>
bool from_string(T& t,
	const std::string& s,
	std::ios_base& (*f)(std::ios_base&))
{
	std::istringstream iss(s);
	return !(iss >> f >> t).fail();
}
void setBoard(Board map)
{
	
	for (int x = 1; x < 7; x++)
	{
		for (int y = 1; y < 7; y++)
		{
			map.addEdge(x, y, x + 1, y);
			map.addEdge(x, y, x, y + 1);
		}
	}
	for (int x = 0; x < 7; x++)
	{
		map.addEdge(x, 0, x + 1, 0);
		map.addEdge(x, 0, x, 1);
	}
	for (int y = 0; y < 7; y++)
	{
		map.addEdge(0, y, 1, y);
		map.addEdge(0, y, 0, y + 1);
		map.addEdge(7, y, 7, y + 1);
	}

	for (int x = 0; x < 7; x++)
	{
		map.addEdge(x, 7, x + 1, 7);
	}
}
int main()
{

	Board map;
	sf::RenderWindow window(sf::VideoMode(816, 816), "CS 2 Game");	 
	window.setKeyRepeatEnabled(false);
	sf::Vector2f vec(816.f, 816.f);
	sf::Vector2u vecu(816.f, 816.f);
	window.setSize(vecu);
	//window.


	sf::RectangleShape boardGame(vec);
	boardGame.setFillColor(sf::Color::Color(128,128,128));
	sf::Clock clock;
	

	sf::Texture tre;
	tre.loadFromFile("walking.jpg");
	sf::Sprite board;
	board.setTexture(tre);
	board.setScale(1, 1.82);

	button easy("Easy Difficulty",.5f);
	easy.setLocation(160, 600);
	button medium("Medium Difficulty",.3f);
	medium.setLocation(160, 640);
	button hard("Hard Difficulty",.2f);
	hard.setLocation(160, 680);
	button impossible("Impossible Difficulty", .15f);
	impossible.setLocation(160, 720);

	for (int x = 0; x < 8; x++)
	{
		for(int y=0;y<8;y++)
			map.addVertex(x,y);
	}



label:
	
	map.buildBoard();
	setBoard(map);
	map.setPlayerLocation(1, 1);
	map.setZombieLocation(1, 7);
	bool moved = false;


	std::ofstream outfile;
	float high;
	string user;

	sf::Music music;
	music.openFromFile("sound.ogg");
	music.setVolume(30);

	sf::Music playSound;
	playSound.openFromFile("funny.ogg");
	playSound.setVolume(50);
	playSound.setLoop(true);

	sf::Music over;
	over.openFromFile("gameover.ogg");
	over.setVolume(100);



	sf::Font font;
	if (!font.loadFromFile("sansation.ttf"))
	{
		return 0;
	}
	TextField name;
	name.setLocation(150, 100);

	sf::Text credits;
	credits.setStyle(sf::Text::Bold);
	credits.setString("Credits: Kevin Kowalski");
	credits.setCharacterSize(30);
	credits.setFillColor(Color::Color(255, 69, 0));
	//credits.setFillColor(Color::Black);
	credits.setFont(font);
	credits.setPosition(480, 780);


	sf::Text lost;
	lost.setStyle(sf::Text::Bold);
	lost.setString("You Lost.... Time Survived: ");
	lost.setCharacterSize(30);
	lost.setOutlineColor(Color::Red);
	lost.setFillColor(Color::Red);
	lost.setFont(font);
	lost.setPosition(150, 350);

	sf::Texture schweller;
	schweller.loadFromFile("schweller.jpg");
	sf::Sprite s;
	s.setTexture(schweller);
	s.setScale(2, 2);


	sf::Clock time;
	float highscore;
	bool here = false;
	music.setLoop(true);
	music.play();
	clock.restart();
	float speed=.5f;
	bool start = false;
while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::TextEntered &&!start)
			{
				if (event.text.unicode == 8)
				{
					name.str = name.str.substr(0, name.str.length() - 1);
					name.text.setString(name.str);
				}
				else if (event.text.unicode>=32 &&event.text.unicode < 128 && name.str.length()<25)
				{
					name.str += static_cast<char>(event.text.unicode);
					name.text.setString(name.str);
				}
				
			}
			if (map.alive() && start)
			{
				if (event.type == sf::Event::KeyPressed &&sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !moved)
				{
					moved = true;
					if (map.getRow() > 0) {
						map.travelTo(map.getRow() - 1, map.getCol());
					}
				}
				else if (event.type == sf::Event::KeyPressed &&sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !moved)
				{
					moved = true;
					if (map.getRow() < 7) {
						map.travelTo(map.getRow() + 1, map.getCol());
					}
				}
				else if (event.type == sf::Event::KeyPressed &&sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !moved)
				{
					moved = true;
					if (map.getCol() > 0) {
						map.travelTo(map.getRow(), map.getCol() - 1);
					}
				}
				else if (event.type == sf::Event::KeyPressed &&sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !moved)
				{
					moved = true;
					if (map.getCol() < 7) {
						map.travelTo(map.getRow(), map.getCol() + 1);
					}
				}
				if (event.type != sf::Event::KeyPressed)
					moved = false;
			}
		}
		if (!start)
		{
			
			window.clear();
			window.draw(board);
			window.draw(credits);
			window.draw(name);
			window.draw(easy);
			window.draw(medium);
			window.draw(hard);
			window.draw(impossible);
			window.display();	
		}
		if (sf::Mouse::isButtonPressed(Mouse::Left) && !start && easy.pressed(event.mouseButton.x,event.mouseButton.y)) {
			std::ifstream infile("HighScore1.txt");
			getline(infile,user);
			string str;
			infile >> str;
			infile.close();
			
			from_string<float>(high, str, std::dec);
			outfile.open("HighScore1.txt");

			playSound.play();

			speed = easy.speed;
			start = true;
			time.restart();
		}
		else if (sf::Mouse::isButtonPressed(Mouse::Left) && !start && medium.pressed(event.mouseButton.x, event.mouseButton.y)) {
			std::ifstream infile("HighScore2.txt");
			getline(infile, user);
			string str;
			infile >> str;
			infile.close();
			playSound.play();

			from_string<float>(high, str, std::dec);
			outfile.open("HighScore2.txt");

			speed = medium.speed;
			start = true;
			time.restart();
		}
		else if (sf::Mouse::isButtonPressed(Mouse::Left) && !start && hard.pressed(event.mouseButton.x, event.mouseButton.y)) {
			std::ifstream infile("HighScore3.txt");
			getline(infile, user);
			string str;
			infile >> str;
			infile.close();
			playSound.play();

			from_string<float>(high, str, std::dec);
			outfile.open("HighScore3.txt");

			speed = hard.speed;
			start = true;
			time.restart();
		}
		else if (sf::Mouse::isButtonPressed(Mouse::Left) && !start && impossible.pressed(event.mouseButton.x, event.mouseButton.y)) {
			std::ifstream infile("HighScore4.txt");
			getline(infile, user);
			string str;
			infile >> str;
			infile.close();
			playSound.play();

			from_string<float>(high, str, std::dec);
			outfile.open("HighScore4.txt");

			speed = impossible.speed;
			start = true;
			time.restart();
		}
		if (start)
		{
			music.stop();
			if (clock.getElapsedTime().asSeconds() >= speed)
			{
				map.BFS();
				clock.restart();
			}
			
			
			window.clear();
			window.draw(boardGame);
			for (int x = 0; x < map.getVertices().size(); x++)
			{
				if (map.getVertices()[x]->value != 'P' &&map.getVertices()[x]->value != 'Z')
					window.draw(map.getVertices()[x]->rect);
				else
					window.draw(map.getVertices()[x]->spr);
			}
			if (!map.alive())
			{
				if (!here) {
					highscore = time.getElapsedTime().asSeconds();
					music.stop();
					playSound.stop();
					over.play();
				}
				
				window.draw(s);
				lost.setString("You Failed The Class.... \nYou are O(N^2), I'm O(N) IM FASTER.\nTime Survived: "+to_string(highscore));
				
				if (highscore > high&& !here)
				{
					outfile << name.str + "\n";
					outfile << to_string(highscore);
					outfile.close();
				}
				else if (highscore < high && !here)
				{
					outfile << user + "\n";
					outfile << to_string(high);
					outfile.close();
				}
				if (highscore < high)
				{
					lost.setString(lost.getString() + "\n\nHighscore: " + to_string(high)+"\nBy "+user);
				}
				if (highscore > high)
				{
					lost.setString(lost.getString()+"\n\nNew Highscore: " + to_string(highscore)+"\nBy "+name.str);
				}
				lost.setString(lost.getString() + "\n\nPress Space to Play Again");
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					here = false;
					start = false;
					map.setPlayerLocation(1, 1);
					map.setZombieLocation(1, 7);
					window.clear();
					over.stop();
					goto label;
				}
				window.draw(lost);
				here = true;
			}

			window.display();
		}
		
	}
	return 0;
}
//317+25+166+55+41