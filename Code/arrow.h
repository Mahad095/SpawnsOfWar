#pragma once
#include"projectile.h"
#include"game.h"
#include<iostream>
class arrow: public projectile
{
public:
		arrow(Vector2f a, Vector2f b, int d, RenderWindow * window, int i)
		{
			img.createImage("projectile", "arrow", "sprites\\archer\\arrow3.png", true);
			id = i;
			img.scale(id / abs(id), 1);
			name = "Arrow";
			start = a;
			end = b;
			dmg = d;
			this->ptrWindow = window;
			hitbox.set(&this->id, &img, img.getSize().x, img.getSize().y, 0);
			this->projectileSpd = 20;
			width = img.getSize().x;
			float theta = atan((end.y - start.y) / (end.x - start.x));
			theta *= 180 / 3.142;
			if (theta < 0 && id!=2) theta += 180;
			img.setOrigin(int(img.getSize().x) / 2, int(img.getSize().y) / 2);
			img.setRotation(theta);
			img.setPosition(start.x, start.y);
			hitbox.setRotation(theta);
		}
};
