#pragma once
#include "troop1.h"
#include"Ranged.h"
class fallenAngel :
    public Ranged
{
	bool activate;
public:
	fallenAngel(RenderWindow* window, std::vector<std::shared_ptr<projectile>>* projectiles, bool boss) {
		activate = false;
		id = -6;
		range = 320;
		health = 300;
		atk = 40;
		weight = 100;
		spd = 4;
		list = projectiles;
		name = "fallenAngel";
		anima.setOffset(-10);
		anima.set(window, "sprites\\fallen angel\\fallen angel1.png", 10, 10, 10);
		anima.img.scale(-1, 1);
		anima.img.setPosition(2 * window->getSize().x + global::originX, anima.img.getPosition().y + anima.getOffset());
		anima.setId(this->id);
		hitbox.set(&this->id, &anima.img, 40, 60, 3);
		hpBar.set(&health, &maxHp, &hitbox, 50, 10);
		maxHp = health;
		maxSpd = spd;
		rangeCircle.set(&hitbox, this->range);
		anima.setScaleFactor(-1);
		bossStatus = boss;
		attackSpd = 700.f;
		if (bossStatus) {
			*this * 10;
			anima.img.setPosition(2 * window->getSize().x + global::originX - 100.f, anima.img.getPosition().y + anima.getOffset());
			move = false;
		}
	}
	void focus(shared_ptr<troop> a) {
		getEnemy(a);
		isAtk = true;
		move = false;
	}
	void unfocus() {
		nullInstance();
		if (!activate)
			activate = (bossStatus && maxHp != health);
		if ((!isPushed() && !bossStatus) || (activate))  //Revisit this condition
			setMove(true);
		setAttack(false);
	}
};

