#pragma once

#include"SFML\Graphics.hpp"
#include<iostream>
using namespace sf;
class image:public Drawable
{
	Texture T;
	Sprite S;
	std::string name;
	std::string type;
	sf::Vector2f SpriteSize;
public:
	image(const image& obj){
		this->T = obj.T;
		this->name = obj.name;
		this->type = obj.type;
		this->S.setTexture(T);
		setOrigin(getWidth() / 2, 0);
		//setPosition(obj.S.getPosition().x - obj.T.getSize().x/2, obj.S.getPosition().y);
		setPosition(obj.getPosition().x, obj.getPosition().y);
		T.setSmooth(true);
		SpriteSize = sf::Vector2f(T.getSize());
	}
	image() {}
	void setTexture(Texture a) {
		S.setTexture(a);
	}
	void createImage(std::string e, std:: string b, std::string a, bool isSmooth) {
		name = b;
		type = e;
		if (!T.loadFromFile(a)) {
			std::cout << "There was an error loading the texture! Exiting";
			exit(-1);
		}
		T.setSmooth(isSmooth);
		S.setTexture(T);
		S.setOrigin(Vector2f(getWidth() / 2, 0));
		SpriteSize = sf::Vector2f(T.getSize());
	}
	std::string getName() {
		return name;
	}
	void changeTexture(std::string a) {
		Texture t;
		t.loadFromFile(a);
		T.update(t);
	}
	void setPosition(float x, float y) {
		S.setPosition(Vector2f(x + getWidth() / 2, y));
	}
	std::string getType() const{
		return type;
	}
	void scale(float x, float y) {
		S.scale(x, y);
	}
	void setOrigin(float a, float b) {
		S.setOrigin(a, b);
	}
	Vector2f getPosition() const{
		Vector2f temp;
		temp.x = S.getPosition().x - getWidth() / 2;
		temp.y = S.getPosition().y;
		return temp;
	}
	Sprite* getSprite() {
		return &S;
	}
	void centerImage(Vector2u a) {
		setPosition(a.x/2 - getSize().x/2, a.y/2 - getSize().y/2);
	}
	Texture* getTexture() {
		return &T;
	}
	void move(float a, float b) {
		this->S.move(a, b);
	}
	FloatRect getGlobalBounds() {
		return S.getGlobalBounds();
	}
	void setTextureRect(const IntRect& a) {
		S.setTextureRect(a);
	}
	Vector2u getSize() {
			return T.getSize();
	}
	float getWidth() const{
		if (getType() != "troop")
			return T.getSize().x;
		else
			return T.getSize().x / unsigned(10);
	}
	void setSize(float a, float b) {
		sf::Vector2f Scale(a / T.getSize().x, b / T.getSize().y);
		SpriteSize.x = Scale.x * T.getSize().x;
		SpriteSize.y = Scale.y * T.getSize().y;
		S.scale(Scale);
		setPosition(S.getPosition().x, S.getPosition().y);
	}
	sf::Vector2f getNewSize() {
		return SpriteSize;
	}
	float getHeight() {
		if (getType() != "troop")
			return T.getSize().y;
		else
			return T.getSize().y / unsigned(3);
	}
	void setRotation(float f) {
		this->S.setRotation(f);
	}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(S);
	}
	bool contains(Vector2f a) {
		if (getGlobalBounds().contains(a)) {
			return true;
		}
		else return false;
	}
};

