#pragma once
#include"Ranged.h"
class wizard:public Ranged
{
public:
	const static int manaPrice = 40;
	wizard(RenderWindow* window, std::vector<std::shared_ptr<projectile>>* projectiles) {
		id = 3;
		name = "wizard";
		range = 300;
		weight = 50;
		health = 150;
		atk = 20;
		spd = 2;
		anima.setOffset(-10);
		anima.set(window, "sprites\\wizard\\wizard.png", 10, 10, 10);
		anima.img.setPosition(-1 * (int(anima.img.getSize().x) / 13) + global::originX, window->getSize().y - anima.img.getTexture()->getSize().y / 3 - window->getSize().y / 4 + anima.getOffset());
		anima.setId(this->id);
		hitbox.set(&this->id, &anima.img, 50, 70, 10);
		hpBar.set(&health, &maxHp, &hitbox, 50, 10);
		list = projectiles;
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

