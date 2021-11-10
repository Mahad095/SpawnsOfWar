#pragma once
#include "troop1.h"
#include"arrow.h"
#include"Ranged.h"
class archer :
    public Ranged
{
public:

	const static int manaPrice = 20;
    archer(RenderWindow* window, std::vector<std::shared_ptr<projectile>>* projectiles) {
		id = 2;
		weight = 30;
		range = 450;
		health = 150;
		name = "Archer";
		atk = 50;
		spd = 2;
		anima.setOffset(-5);
		anima.set(window, "sprites\\archer\\archerSpriteSheet1.png", 10, 10, 10);
		anima.img.setPosition(-1 * (int(anima.img.getSize().x) / 13) + global::originX, window->getSize().y - anima.img.getTexture()->getSize().y / 3 - window->getSize().y / 4 + anima.getOffset());
		anima.setId(this->id);
		hitbox.set(&this->id, &anima.img, 50, 70, 7);
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

