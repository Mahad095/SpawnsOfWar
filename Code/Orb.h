#pragma once
#include "projectile.h"
class Orb :
    public projectile
{
public:
    Orb(Vector2f a, Vector2f b, int d, RenderWindow* window, int i) {
        img.createImage("projectile", "Orb", "sprites\\wizard\\orb1.png", true);
		id = i;
		img.scale(id / abs(id), 1);
		name = "Orb";
		start = a;
		end = b;
		dmg = d;
		this->ptrWindow = window;
		hitbox.set(&this->id, &img, img.getSize().x, img.getSize().y, 0);
		this->projectileSpd = 10;
		img.setPosition(start.x, start.y);
		width = img.getSize().x;
		splashRange = 100;
		splash = true;
    }
	void damage(std::shared_ptr<troop> enemy) {
		if (enemy != nullptr && !remove) {
			enemy->takeDamage(this->dmg);
			enemy->setSpd(enemy->getMaxSpd() / 4.f);
			enemy->anima.img.getSprite()->setColor(Color(90, 223, 255, 255));
			enemy->restart_Clock(2);
		}
	}
};
