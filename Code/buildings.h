#pragma once
#include"Hitbox.h"
#include"image.h"
#include"healthBar.h"
class building
{
protected:
	int hp;
	int atk;
	int maxHp;
	RenderWindow* ptrWindow;
	bool remove;
public:
	Hitbox hitbox;
	image img;
	healthBar hpbar;
	building(){
		hp = 0;
		maxHp = 0;
		ptrWindow = nullptr;
		atk = 0;
		remove = false;
	}
	~building() {
	}
	void setRemove(bool cond) {
		remove = cond;
	}
	bool isRemove() {
		return remove;
	}
	void setHp(int a) {
		hp = a;
	}
	int getMaxHp() {
		return maxHp;
	}
	void takeDamage(int atk) {
		if (hp - atk > 0)
			this->hp -= atk;
		else
			hp = 0;
	}
	virtual void update() {
		hitbox.update();
		hpbar.update();
	}
	 virtual void draw() {
		ptrWindow->draw(hitbox.getBar());
		ptrWindow->draw(*img.getSprite());
		ptrWindow->draw(hpbar.getBar());
	}
	 virtual void updatePosition() {
		 img.move(global::windowOffset, 0);
	 }
};

