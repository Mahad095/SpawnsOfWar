#pragma once
#include"SFML/Graphics.hpp"
#include <time.h>
class Particles
{
protected:
	sf::CircleShape p;
	float scale;
	sf::Vector2f spd;
	sf::Vector2f initialCoordinates;
	sf::RenderWindow* ptrWindow;
	int alpha;
	bool remove;
public:
	bool isRemove() {
		return remove;
	}
	void setRemove(bool a) {
		remove = a;
	}
	Particles(){}
	 Particles(sf::RenderWindow& window) {
		scale = 15;
		remove = false;
		alpha = 220;
		ptrWindow = &window;
		p.setRadius(scale);
		spd.x = (rand() % 10) + (-4);
		spd.y = (rand() % 5) + (-5);
		initialCoordinates.x = sf::Mouse::getPosition(*ptrWindow).x;
		initialCoordinates.y = sf::Mouse::getPosition(*ptrWindow).y;
		p.setPosition(initialCoordinates);
		p.setFillColor(sf::Color(255, 255, 255, alpha));
	}

	virtual void update() {
		if(scale > 0)
		scale -= 0.5;
		alpha -= 5;
		p.setRadius(scale);
		spd.x = (rand() % 10) + (-4);
		spd.y = (rand() % 5) + (-5);
		initialCoordinates.x += spd.x;
		initialCoordinates.y += spd.y;
		p.setPosition(initialCoordinates);
		p.setFillColor(sf::Color(255, 255, 255, alpha));
	}
	int getAlpha() {
		return this->alpha;
	}
	virtual void draw() {
		this->ptrWindow->draw(p);
	}
	virtual void updatePosition() = 0;
};

