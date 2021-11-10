#pragma once
#include"SFML/Graphics.hpp"
#include"Hitbox.h"
class RangeCircle
{
	sf::CircleShape circle;
	Hitbox* ptrHitbox;

public:
	RangeCircle() {
		circle.setFillColor(sf::Color::Transparent);
	}
	bool inRange(Hitbox a) {
		if (circle.getGlobalBounds().intersects(a.getBar().getGlobalBounds())) {
			return true;
		}
		else return false;
	}
	void set(Hitbox* a, float r) {
		ptrHitbox = a;
		circle.setRadius(r);
		update();
	}
	void setRadius(float a) {
		circle.setRadius(a);
	}
	void setPosition(float a, float b) {
		circle.setPosition(a, b);
	}
	float getRadius() {
		return circle.getRadius();
	}
	sf::Vector2f getPosition() {
		return circle.getPosition();
	}
	void update() {
		setPosition(ptrHitbox->getPosition().x + ptrHitbox->getSize().x / 2 - getRadius() , ptrHitbox->getPosition().y + ptrHitbox->getSize().y / 2 - getRadius());
	
	}
	CircleShape getCircle() {
		return circle;
	}
};

