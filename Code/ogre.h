#pragma once
#include"Troop1.h"

class ogre :public troop {
public:
	ogre(RenderWindow* window) {
		id = -9;
		range = 35;
		health = 300;
		weight = 15;
		atk = 40;
		spd = 4;
		name = "Ogre";
		anima.setOffset(-15);
		anima.set(window, "sprites\\ogre\\ogre.png",10,10,10);
		anima.img.scale(-1, 1);
		anima.img.setPosition(2 * window->getSize().x + global::originX, anima.img.getPosition().y + anima.getOffset());
		anima.setId(this->id);
		hitbox.set(&this->id, &anima.img, 40, 60, 3);
		hpBar.set(&health, &maxHp, &hitbox, 50, 10);
		maxHp = health;
		maxSpd = spd;
		rangeCircle.set(&hitbox, this->range);
		anima.setScaleFactor(-1);
	}
	void focus(shared_ptr<troop> a) {
		getEnemy(a);
		isAtk = true;
		move = false;
	}
};