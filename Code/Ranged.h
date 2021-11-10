#pragma once
#include"troop1.h"
#include"projectile.h"
#include"arrow.h"
#include"Orb.h"
#include"windSplash.h"
class Ranged :
    public troop
{
public:
	void damage()
	{
		if (clock[1].getElapsedTime().asMilliseconds() >= 400) {
			Vector2f playerMid(hitbox.getPosition().x + hitbox.getSize().x, hitbox.getPosition().y + hitbox.getSize().y / 2);
			Vector2f targetMid;
			if (ptr != nullptr) 
			{
				targetMid.x = getEnemyInstance()->hitbox.getPosition().x;
				targetMid.y = getEnemyInstance()->hitbox.getPosition().y + getEnemyInstance()->hitbox.getSize().y / 2;
			}
			else if (ptrBuilding != nullptr)
			{
				targetMid.x = ptrBuilding->hitbox.getPosition().x;
				targetMid.y = ptrBuilding->hitbox.getPosition().y + ptrBuilding->hitbox.getSize().y / 2;
			}
			if (abs(id) == 2)
			{
				list->push_back(std::shared_ptr<arrow>(new arrow(playerMid, targetMid, getAtkValue(), anima.ptrWindow, this->id)));
			}
			if (abs(id) == 3)
			{
				list->push_back(std::shared_ptr<Orb>(new Orb(playerMid, targetMid, getAtkValue(), anima.ptrWindow, this->id)));
			}
			if (abs(id) == 6)
			{
				list->push_back(std::shared_ptr<windSplash>(new windSplash(playerMid, targetMid, anima.ptrWindow, this->id)));
			}
			clock[1].restart();
		}
	}
};