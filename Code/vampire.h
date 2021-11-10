#pragma once
#include "troop1.h"
class vampire :
    public troop
{
	bool activate;
public:
	~vampire() {
	}
	vampire(RenderWindow* window, bool boss) {
		activate = false;
		id = -7;
		range = 40;
		health = 600;
		atk = 80;
		weight = 100;
		spd = 2;
		name = "vampire";
		anima.setOffset(-10);
		anima.set(window, "sprites\\vampire\\vampire1.png", 10, 10, 10);
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
	void leechLife() {
		int AtkValue = (0.1) * ptr->getAtkValue();
		if(ptr->getAtkValue() - AtkValue >= 0)
			ptr->setAtkValue(ptr->getAtkValue() - AtkValue);
		
		this->atk += AtkValue;
		int reducedHealth = ptr->getHealth() - atk;
		if (reducedHealth > 0)
			ptr->setHealth(reducedHealth);
		else
			ptr->setHealth(0);
		if (health + atk <= maxHp)
			this->health += atk;
		else
			this->health = maxHp;	
	}
	void damage() {
		if (ptr != nullptr)
		{
			leechLife();
		}
		else if (ptrBuilding != nullptr)
		{
			ptrBuilding->takeDamage(atk);
		}
	}

};