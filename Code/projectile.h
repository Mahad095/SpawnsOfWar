#pragma once
#include"image.h"
#include<math.h>
#include"Hitbox.h"
#include"troop1.h"
#include"global.h"
using namespace std;
class projectile
{
protected:
	int id;
	float projectileSpd;
	Vector2f start;
	std::string name;
	Vector2f end;
	bool remove;
	int dmg;
	RenderWindow* ptrWindow;
	float width;
	float splashRange;
public:
	projectile() {
		splash = false;
		remove = false;
		splashRange = 0;
	}
	bool splash;
	Hitbox hitbox;
	image img;
	string getName() {
		return this->name;
	}
	bool isSplash() {
		return splash;
	}
	float getSplashRange() {
		return splashRange;
	}
	virtual void moveToNextPoint() 
	{
		Vector2f aimDir = end - start;
		Vector2f aimDirNorm;
		aimDirNorm = aimDir / sqrt(aimDir.x * aimDir.x + aimDir.y * aimDir.y);
		Vector2f currVelocity = projectileSpd * aimDirNorm;
		img.move(currVelocity.x,currVelocity.y);
	}
	int getId() {
		return this->id;
	}
	int getDamage() {
		return dmg;
	}
	virtual void damage(std::shared_ptr<troop> enemy) {
		if (enemy != nullptr && !remove) {
			enemy->takeDamage(this->dmg);
		}
		remove = true;
	}
	void setRemove(bool cond) {
		remove = cond;
	}
	virtual void updatePosition() {
		end.x += global::windowOffset;
		start.x += global::windowOffset;
		img.move(global::windowOffset, 0);
	}
	void update() {
		if (!remove) {
			moveToNextPoint();
			hitbox.update();
		}
		if (outOfBounds()) remove = true;
	}
	bool outOfBounds() {
		if (img.getPosition().x > 2000 || img.getPosition().x < -2000 || img.getPosition().y > 1000 || img.getPosition().y < -1000)
		{
			return true;
		}
		else return false;
	}
	bool isRemove() {
		return remove;
	}
	void draw() {
		if (!remove) {
				this->ptrWindow->draw(*this->img.getSprite());
				this->ptrWindow->draw(this->hitbox.getBar());
		}

	}
};

