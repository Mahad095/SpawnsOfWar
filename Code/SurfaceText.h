#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"myText.h"
#pragma once
class SurfaceText:public myText
{
	sf::Sprite S;
	sf::Texture T;
	sf::Vector2f SpriteSize;
public:
	SurfaceText() {}
	SurfaceText(const SurfaceText& obj) {
		this->T = obj.T;
		this->S.setTexture(this->T);
		this->font = obj.font;
		this->text.setFont(this->font);
		setSize(obj.getSize().x, obj.getSize().y);
		this->text.setOrigin(int(text.getLocalBounds().left + text.getLocalBounds().width / 2.0f), int(text.getLocalBounds().top + text.getLocalBounds().height / 2.0f));
		setFillColor(obj.getFillColor());
		setString(obj.getString());
		setPosition(obj.getPosition().x, obj.getPosition().y);
	}
	void set(std::string img) {
		if (!T.loadFromFile(img)) {
			std::cout << "ERROR IN LOADING image!" << std::endl;
		}
		S.setTexture(T);
		setPosition(0, 0);
		SpriteSize = sf::Vector2f(T.getSize());
		text.setOrigin(int(text.getLocalBounds().left + text.getLocalBounds().width / 2.0f),int( text.getLocalBounds().top + text.getLocalBounds().height / 2.0f));
	}
	void setPosition(float a, float c) {
		S.setPosition(a, c);
		text.setPosition(a + getSize().x / 2 - text.getLocalBounds().width / 2, c + getSize().y / 2 - text.getLocalBounds().height / 2 - text.getLocalBounds().top);
	}
	Vector2f getPosition() const{
		return S.getPosition();
	}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(S);
		target.draw(text);
	}
	void setSize(float a, float b) {
		sf::Vector2f Scale(a / T.getSize().x, b / T.getSize().y);
		SpriteSize.x = Scale.x * T.getSize().x;
		SpriteSize.y = Scale.y * T.getSize().y;
		S.scale(Scale);
		setPosition(S.getPosition().x, S.getPosition().y);
	}
	sf::Vector2f getSize() const{
		return SpriteSize;
	}
	sf::Sprite* getSprite() {
		return &S;
	}
	bool contains(Vector2f a) {
		if (S.getGlobalBounds().contains(a)) {
			return true;
		}
		else return false;
	}
};



