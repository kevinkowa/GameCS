#include<iostream>
#include<SFML\Graphics.hpp>
#include<vector>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Export.hpp>
#include <SFML\Graphics\Texture.hpp>
using namespace std;

class vertex
{
public:
	sf::RectangleShape rect;
	int row;
	int col;
	vertex* predecesor;
	char value;
	sf::Sprite spr;
	vector<vertex*>neighbours;
	vertex(int r, int c)
	{
		row = r;
		col = c;
		value = ' ';
	}
};