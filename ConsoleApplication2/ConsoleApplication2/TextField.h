#include<iostream>
#include<SFML\Graphics.hpp>

using namespace std;
using namespace sf;

class TextField :public sf::Drawable, sf::Transformable {

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const
	{
		states.transform *= getTransform();
		target.draw(rec, states);
		target.draw(text, states);
	}
public:
	string str;
	RectangleShape rec;
	Text text;
	Font font;
	TextField()
	{
		str = "";
		font.loadFromFile("sansation.ttf");
		this->text.setStyle(sf::Text::Bold);
		this->text.setCharacterSize(30);
		this->text.setOutlineColor(Color::Red);
		this->text.setFillColor(Color::Red);
		this->text.setFont(font);
		this->text.setPosition(150, 300);
		this->text.setString("Type Your Name Here");
		Vector2f vec(25* 15, 35);
		rec.setSize(vec);
		rec.setFillColor(Color::Cyan);
		rec.setPosition(150, 300);
	}
	void setLocation(int x, int y)
	{
		rec.setPosition(x, y);
		text.setPosition(x, y);
	}


};