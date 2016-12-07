#pragma once
#include<iostream>
#include<string>
#include<queue>
#include <SFML/Audio.hpp>
#include "undirectedGraph.h"
using namespace std;
class Board : public undirectedGraph
{
private:
	vertex * playerVertex;
	vertex * Zombie;
	sf::Texture glen;
	sf::Texture schweller;	
	int points;
public:
	Board()
	{
		schweller.loadFromFile("schweller.jpg");
		glen.loadFromFile("glen.jpg");
	}
	bool alive()
	{
		if (abs(Zombie->row - playerVertex->row) <= 0 && abs(Zombie->col - playerVertex->col) <= 0)
		{
			cout << "YOU LOST...";
			return false;
		}
		return true;
	}
	int getRow()
	{
		return playerVertex->row;
	}
	char getCol()
	{
		return playerVertex->col;
	}
	void setPlayerLocation(int num, int pos)
	{
		vertex* dest = find(num, pos);
		if (dest->value == 'Z')
			return;
		if (playerVertex != NULL)
			playerVertex->value = ' ';
		playerVertex = dest;
		playerVertex->value = 'P';
		playerVertex->spr.setTexture(glen, true);
		playerVertex->spr.setScale(.14, .27);
		playerVertex->spr.setOrigin(40, 40);
		playerVertex->spr.setPosition(16+num*100, 20+pos*100);
	}
	void setZombieLocation(int num, int pos)
	{
		if (Zombie != NULL)
			Zombie->value = ' ';
		Zombie = find(num, pos);
		Zombie->value = 'Z';
		Zombie->spr.setTexture(schweller, true);
		Zombie->spr.setScale(.223,.21);
		Zombie->spr.setOrigin(40, 40);
		Zombie->spr.setPosition(16 + num * 100, 20 + pos * 100);

	}

	void buildBoard()
	{

		int row = 0;
		int curr = 0;
		for (int x = 0; x <8; x++)
		{
			int col = 0;
			for (int y = 0; y < 8; y++)
			{
				vertices[curr]->rect.setSize(sf::Vector2f(81.6f + 10, 81.6f + 10));
				vertices[curr]->rect.setPosition(sf::Vector2f(row + 10, col + 10));
				vertices[curr]->rect.setFillColor(sf::Color::White);
				curr++;
				col += 100;
			}
			row += 100;
		}

	}
	string getPlayerLocationExits()
	{
		string paths = "";
		if (playerVertex->neighbours.size() == 0)
			return "There aint none";
		for (int x = 0; x < playerVertex->neighbours.size() - 1; x++)
		{
			paths += "(" + to_string(playerVertex->neighbours[x]->row) + ", " + to_string(playerVertex->neighbours[x]->col) + "), ";
		}
		paths += "(" + to_string(playerVertex->neighbours[playerVertex->neighbours.size() - 1]->row) + ", " + to_string(playerVertex->neighbours[playerVertex->neighbours.size() - 1]->col) + ").";
		return paths;
	}
	bool travelTo(int row, int col)
	{
		bool found = false;
		for (int x = 0; x < playerVertex->neighbours.size(); x++)
		{
			if (playerVertex->neighbours[x]->row == row && playerVertex->neighbours[x]->col == col)
			{
				if (playerVertex->neighbours[x]->value == 'Z')
					return false;
				playerVertex->value = ' ';
				playerVertex->neighbours[x]->value = 'P';
				sf::Sprite s;
				sf::Sprite copy = playerVertex->spr;
				playerVertex->spr =s;
				playerVertex = playerVertex->neighbours[x];
				playerVertex->value = 'P';
				playerVertex->spr = copy;
				playerVertex->spr.setPosition(16 + row * 100, 20 + col * 100);
				found = true;
				break;
			}
		}
		return found;
	}
	void Points()
	{
		cout << "You have: " << points << " points" << endl;
	}
	bool BFS()
	{
		vertex*target = playerVertex;
		if (target == Zombie)
		{
			cout << "You lost..." << endl;
			return false;
		}
		string path = "";
		queue<vertex*>vec;
		vector<vertex*>visited;
		vec.push(Zombie);
		visited.push_back(Zombie);
		while (!vec.empty())
		{
			vertex*curr = vec.front();
			vec.pop();

			for (int x = 0; x<curr->neighbours.size(); x++)
			{
				vertex*next = curr->neighbours[x];
				if (std::find(visited.begin(), visited.end(), next) == visited.end())
				{

					next->predecesor = curr;
					curr->neighbours[x] = next;
					vec.push(next);
					visited.push_back(next);
				}
			}
		}
		while (target->predecesor != Zombie)
		{
			target = target->predecesor;
		}
		setZombieLocation(target->row, target->col);
		return true;

	}

};