#pragma once
#include "troop1.h"
class troll :
    public troop
{
public:
	const static int manaPrice = 60;
	troll(RenderWindow* window) {
		id = 4;
		range = 120;
		health = 1500;
		weight = 100;
		atk = 110;
		spd = 1;
		name = "Troll";
		anima.set(window, "sprites\\troll\\troll1.png", 10, 10, 10);
		anima.img.setPosition(-1 * (int(anima.img.getSize().x) / 13) + global::originX, window->getSize().y - anima.img.getTexture()->getSize().y / 3 - window->getSize().y / 4 + anima.getOffset());
		anima.setId(this->id);
		hitbox.set(&this->id, &anima.img, 100, 120, 20);
		hpBar.set(&health, &maxHp, &hitbox, 50, 10);
		maxHp = health;
		maxSpd = spd;
		rangeCircle.set(&hitbox, this->range);
		anima.setScaleFactor(1);

	}
	void focus(shared_ptr<troop> a) {
		getEnemy(a);
		isAtk = true;
		move = false;
	}
};

