#pragma once
#include"bars.h"
#include"Hitbox.h"
class healthBar:public Bars
{
	int* currhealth;
	int* totalHealth;
	float maxWidth;
	Hitbox* ptrBox;
	void changeSize() {
		float x = (float(*currhealth) / float(*totalHealth)) * maxWidth;
		if (x > 0) {
			this->setSize(x, getSize().y);
		}
	}
public:
	healthBar() {
		this->setFillColor(Color::Green);
	}	
	void set(int* hp1, int* hp2, Hitbox* a, float b, float c) {
		this->currhealth = hp1;
		this->totalHealth = hp2;
		ptrBox = a;
		this->setSize(b, c);
		maxWidth = b;
	}
	void update() {
		changeSize();
		setPosition(ptrBox->getPosition().x + ptrBox->getSize().x/2 - maxWidth/2, ptrBox->getPosition().y - 15); //25 is the half of original value
	}
};

