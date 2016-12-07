#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>
#include<string>
#include<iostream>

using namespace sf;
using namespace std;
class button:public sf::Drawable,sf::Transformable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const
	{
		states.transform *= getTransform();
		target.draw(rec, states);
		target.draw(text, states);
	}
public:
	RectangleShape rec;
	Text text;
	Font font;
	float speed;

	button(string text,float sp)
	{
		speed = sp;
		font.loadFromFile("sansation.ttf");
		this->text.setStyle(sf::Text::Bold);
		this->text.setCharacterSize(30);
		this->text.setOutlineColor(Color::Red);
		this->text.setFillColor(Color::Red);
		this->text.setFont(font);
		this->text.setPosition(150, 300);
		this->text.setString(text);
		Vector2f vec(text.size()*15,35);
		rec.setSize(vec);
		rec.setFillColor(Color::Transparent);
		rec.setPosition(150, 300);
	}
	void setLocation(int x, int y)
	{
		rec.setPosition(x, y);
		text.setPosition(x, y);
	}
	bool pressed(float x,float y)
	{
		Vector2f vec(x, y);
		if (rec.getGlobalBounds().contains(vec))
			return true;
		return false;

	}


};