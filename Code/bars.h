#pragma once
#include"SFML/Graphics.hpp"
using namespace sf;
class Bars
{
protected:
	RectangleShape bar;
public:
	Vector2f getPosition() {
		return this->bar.getPosition();
	}
	void setPosition(float a,float b) {
		bar.setPosition(Vector2f(a, b));
	}
	void setSize(float a, float b) {
		bar.setSize(Vector2f(a, b));
	}
	Vector2f getSize() {
		return bar.getSize();
	}
	RectangleShape getBar() {
		return this->bar;
	}
	void setFillColor(const Color &color) {
		bar.setFillColor(color);
	}
};

