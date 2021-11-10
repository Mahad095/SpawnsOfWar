#include"SFML/Graphics.hpp"
#include"myText.h"
#include<iostream>
#pragma once
using namespace sf;
using namespace std;

class ErrorMessage: public myText
{
	RenderWindow* ptrWindow;
	int r, g, b, a;
	bool remove;
	sf::SoundBuffer buf;
	sf::Sound sound;
public:
	ErrorMessage(RenderWindow* window,string set,unsigned int a){
		text.setString(set);
		text.setCharacterSize(a);
		a = 255;
		r = 255;
		g = 90;
		b = 90;
		text.setFillColor(Color(r, g, b, a));
		ptrWindow = window;
		text.setOrigin(int(text.getLocalBounds().left + text.getLocalBounds().width / 2.0f), int(text.getLocalBounds().top + text.getLocalBounds().height / 2.0f));
		setPosition(ptrWindow->getSize().x / 2 , ptrWindow->getSize().y / 2 );
		remove = false;
		buf.loadFromFile("Sounds\\ClickError.wav");
		sound.setBuffer(buf);
		sound.play();
	}
	void setRemove(bool cond) {
		remove = cond;
	}
	bool isRemove() {
		return remove;
	}
	void update() {
		text.move(0, -0.4);
		if (g + 5 < 255 || b + 5 < 255 || a - 5 > 0)
			text.setFillColor(Color(255, g += 5, b += 5, a -= 5));
		else
			remove = true;
	}
	void draw() {
		ptrWindow->draw(text);
	}
};

