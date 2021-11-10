#pragma once
#include"SFML/Graphics.hpp"
#include<iostream>
class myText: public sf::Drawable
{
protected:
	sf::Font font;
	sf::Text text;
public:
	myText(){
		if (!font.loadFromFile("fonts\\GAMERIA.ttf")) {
			std::cout << "ERROR IN LOADING FONT!" << std::endl;
		}
		text.setFont(font);
		setString("");
	}
	myText(const myText& obj) {
		this->font = obj.font;
		this->text.setFont(this->font);
		this->setFillColor(obj.getFillColor());
		this->setCharacterSize(obj.getCharacterSize());
		this->setString(obj.getString());
		this->setPosition(obj.getPosition().x, obj.getPosition().y);
	}
	virtual void setPosition(float a, float c) {
		text.setPosition(a, c);
	}
	virtual void setFont(Font a) {
		text.setFont(a);
	}
	virtual void setString(std::string a) {
		text.setString(a);
	}
	virtual std::string getString() const{
		return text.getString();
	}
	virtual void setCharacterSize(unsigned int a) {
		text.setCharacterSize(a);
	}
	virtual unsigned int getCharacterSize() const{
		return text.getCharacterSize();
	}
	virtual sf::Vector2f getPosition() const{
		return text.getPosition();
	}
	virtual void setLineSpacing(float a) {
		text.setLineSpacing(a);
	}
	virtual float getLineSpacing() {
		return text.getLineSpacing();
	}
	virtual void setFont(string path) {
		font.loadFromFile(path);
		text.setFont(font);
	}
	virtual void setFillColor(const sf::Color& a) {
		text.setFillColor(a);
	}
	virtual Color getFillColor() const{
		return text.getFillColor();
	}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(text);
	}
	virtual sf::Vector2f getSize() {
		sf::Vector2f size;
		size.x = text.getLocalBounds().width;
		size.y = text.getLocalBounds().height;
		return size;
	}
	virtual Text getText() {
		return text;
	}
	virtual bool contains(Vector2f a) {
		if (text.getGlobalBounds().contains(a)) {
			return true;
		}
		else return false;
	}
};

