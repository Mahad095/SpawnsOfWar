#pragma once
#include "troop1.h"
class demonKing :
    public troop
{
	int lives;
	bool activate;
public:
	demonKing(RenderWindow* window, bool boss) {
		activate = false;
		lives = 4;
		id = -8;
		range = 50;
		health = 450;
		weight = 100;
		atk = 200;
		spd = 1;
		name = "demonKing";
		anima.setOffset(-10);
		anima.set(window, "sprites\\demon king\\demon king1.png", 10, 10, 10);
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
	void damage() {
		if (ptr != nullptr) 
		{
			ptr->kill();
		}
		else if (ptrBuilding != nullptr)
		{
			ptrBuilding->takeDamage(atk);
		}
	}
	bool die() {
		if (anima.getFrames() <= anima.getNoOfFrames("f3") - 1) {
			if (clock[0].getElapsedTime().asMilliseconds() >= delay) {
				anima.rectChange(2, anima.getNoOfFrames("f3"));
				anima.incrementFrames();
				clock[0].restart();
			}
		}
		else{
			if (clock[0].getElapsedTime().asMilliseconds() >= 2000) {
				anima.setFrames(0);
				clock[0].restart();
				if (lives > 1) {
					this->dead = false;
					this->move = true;
					maxHp += 1000;
					health = maxHp;
					lives--;
					return false;
				}
				else return true;
			}
		}
		return false;
	}

};

