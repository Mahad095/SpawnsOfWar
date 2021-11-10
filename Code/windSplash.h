#pragma once
#include "projectile.h"
class windSplash :
    public projectile
{
public:
    windSplash(Vector2f a, Vector2f b, RenderWindow* window, int i) {
		img.createImage("projectile", "windSplash", "sprites\\fallen angel\\wind attack1.png", true);
		id = i;
		img.scale(id / abs(id), 1);
		img.setOrigin(0, img.getSize().y / 2);
		name = "windSplash";
		start = a;
		dmg = 50;
		end = b;
		this->ptrWindow = window;
		hitbox.set(&this->id, &img, img.getSize().x, img.getSize().y, 0);
		this->projectileSpd = 5;
		width = img.getSize().x;
		img.setPosition(start.x , start.y);
    }

	void damage(std::shared_ptr<troop> enemy) {
		enemy->push(true);
		enemy->setMove(false);
		enemy->takeDamage(dmg);
		enemy->restart_Clock(3);
		
	}
};

