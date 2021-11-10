#pragma once
#include"Troop1.h"
class knight :public troop {
public:
	const static int manaPrice = 10;
	knight(RenderWindow* window){
		id = 1;
		name = "knight";
		range = 40;
		health = 300;
		atk = 50;
		spd = 3.5;
		anima.set(window, "sprites\\knight\\knight.png",10, 10, 10);
		anima.img.setPosition(-1 * (int(anima.img.getSize().x) / 13) + global::originX, window->getSize().y - anima.img.getTexture()->getSize().y / 3 - window->getSize().y / 4 + anima.getOffset());
		anima.setId(this->id);
		hitbox.set(&this->id, &anima.img, 40, 60, -5);
		hpBar.set(&health, &maxHp, &hitbox, 50, 10);
		maxHp = health;
		maxSpd = spd;
		rangeCircle.set(&hitbox, this->range);
		weight = 20;
		anima.setScaleFactor(1);
	}
	void focus(shared_ptr<troop> a) {
		getEnemy(a);
		isAtk = true;
		move = false;
	}
};