#pragma once
#include "troop1.h"
#include"knight.h"
class Howl :
    public troop
{
	bool posession;
	int alpha;
	std::vector<std::shared_ptr<troop>>* enemies;
public:
    Howl(RenderWindow* window, std::vector<std::shared_ptr<troop>>& list2) {
		id = -8;
		name = "Howl";
		range = 30;
		weight = 20;
		health = 90;
		atk = 20;
		spd = 5;
		anima.set(window, "sprites\\Howl\\Howl1.png", 10, 10, 10);
		anima.img.scale(-1, 1);
		anima.setId(this->id);
		anima.setOffset(-20);
		anima.img.setPosition(2 * window->getSize().x + global::originX, anima.img.getPosition().y + anima.getOffset());
		hitbox.set(&this->id, &anima.img, 35, 50, -5);
		hpBar.set(&health, &maxHp, &hitbox, 50, 10);
		enemies = &list2;
		posession = false;
		alpha = 255;
		maxHp = health;
		maxSpd = spd;
		rangeCircle.set(&hitbox, this->range);
		anima.setScaleFactor(-1);
	}
	void damage() {
		if (ptr != nullptr) {
			if (ptr->getId() > 0) {
				ptr->setId(ptr->getId() * -1);
				ptr->anima.img.getSprite()->setColor(Color(255, 0, 0, 200)); //setting a mask on posessed enemy
				enemies->push_back(ptr);
				dead = true;
				posession = true;       // howl has 2 death animations. if it posesses someone then it has a fading animation else it has a normal dying one
				isAtk = false;
				move = false;
			}
		}
		else if (ptrBuilding != nullptr) 
		{
			ptrBuilding->takeDamage(atk);
		}
	}
	bool die() {
		if (!posession) {
			if (clock[0].getElapsedTime().asMilliseconds() >= delay) {
				anima.rectChange(2, anima.getNoOfFrames("f3"));
				anima.incrementFrames();
				clock[0].restart();
			}
			if (anima.getFrames() >= anima.getNoOfFrames("f3") - 1) {
				anima.setFrames(0);
				return true;
			}
			else return false;
		}
		else {
			anima.img.getSprite()->setColor(Color(255,255,255,alpha));
			alpha -= 15;
			anima.img.setPosition(anima.img.getPosition().x, anima.img.getPosition().y - 5);
			if (alpha <= 0) {
				return true;
			}
			else
				return false;
		}
	}
	void focus(shared_ptr<troop> a) {
		getEnemy(a);
		isAtk = true;
		move = false;
	}
};
