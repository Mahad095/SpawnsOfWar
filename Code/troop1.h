#pragma once
#include"animation.h"
#include"castle.h"
#include"global.h"
#include"StoppableClock.h"
#include<iostream>
using namespace sf;
using namespace std;

enum clocks {
	ANIMADELAY,
	RANGEDDELAY,
	EFFECTWEAROFF,
	PUSH,
	ATTACKSPEED
};
class projectile;
class troop {
protected:
	const static int manaPrice = 0;
	std::vector<std::shared_ptr<projectile>>* list;
	std::shared_ptr<troop> ptr = nullptr;
	shared_ptr<building> ptrBuilding;
	std::string name;
	int id;
	int health;
	int range;
	int atk;
	int maxHp;
	float maxSpd;
	float spd;
	float weight;
	bool move;
	bool isAtk;
	bool dead;
	bool remove;
	bool walkAnima;
	StoppableClock clock[5];
	float delay;
	bool heal;
	bool beingPushed;
	bool bossStatus;
	float attackSpd;
public:
	class animation anima;
	Hitbox hitbox;
	healthBar hpBar;
	RangeCircle rangeCircle;
	std::string getName() {
		return name;
	}
	int getMaxHealth() {
		return maxHp;
	}
	float getMaxSpd() {
		return this->maxSpd;
	}
	void setSpd(float a) {
		spd = a;
	}

	troop() {
		this->move = true;
		this->isAtk = false;
		this->dead = false;
		this->remove = false;
		this->walkAnima = false;
		anima.setOffset(0);
		delay = 40;
		list = nullptr;
		heal = false;
		ptrBuilding = nullptr;
		beingPushed = false;
		bossStatus = false;
		attackSpd = 500.f;
	}
	float getWeight() {
		return weight;
	}
	bool isHealing() {
		return heal;
	}
	void getBuilding(shared_ptr<building>  a) {
		ptrBuilding = a;
	}
	void setHeal(bool a) {
		heal = a;
	}
	bool isRemove() {
		return remove;
	}
	void updatePosition() {
		anima.img.move(global::windowOffset, 0);
	}
	~troop() {
	}
	void setRemove(bool a) {
		this->remove = a;
	}
	void getEnemy(std::shared_ptr<troop> enemy) {
		if (this->ptr == nullptr) {
			ptr = enemy;
			ptrBuilding = nullptr; //if enemy ptr is available then we null the castle
		}
	}
	void effectWearOff() {
		if (maxSpd != spd) {
			if (clock[EFFECTWEAROFF].getElapsedTime().asMilliseconds() >= 3000) {
				spd = maxSpd;
				anima.img.getSprite()->setColor(Color(255, 255, 255, 255));
				clock[EFFECTWEAROFF].restart();
			}
		}
	}
	void takeDamage(int a) {
		this->health -= a;
	}
	int getHealth() {
		return this->health;
	}
	bool isEnemyDead() {
		if (ptr != nullptr)
			return this->ptr->dead;
		else return true;
	}
	virtual void damage() {
		if (ptr != nullptr)
			ptr->health -= this->atk;
		else if (ptrBuilding != nullptr) {
			ptrBuilding->takeDamage(atk);
		}
	}
	void nullInstance() {
		this->ptr = nullptr;
	}
	bool isMoving() {
		return this->move;
	}
	bool isAttacking() {
		return this->isAtk;
	}
	bool isDead() {
		return dead;
	}
	int getRange() {
		return this->range;
	}
	void setMove(bool cond) {
		this->move = cond;
	}
	void setHealth(int a) {
		health = a;
	}
	void setAttack(bool cond) {
		this->isAtk = cond;
	}
	void setDead(bool cond) {
		if (this->dead != cond) {
			this->dead = cond;
			this->anima.setFrames(0);
		}
	}
	void setId(int a) {
		id = a;
	}
	int getSpeed() {
		return this->spd;
	}
	int getId() {
		return this->id;
	}
	void restart_Clock(int i) {
		clock[i].restart();
	}
	void walk() {

		if (clock[ANIMADELAY].getElapsedTime().asMilliseconds() >= delay) {
			anima.rectChange(0, anima.getNoOfFrames("f1"));
			if (walkAnima) {
				if (anima.getFrames() - 1 >= 0)
					anima.decrementFrames();
			}
			else {
				if (anima.getFrames() + 1 <= 9)
					anima.incrementFrames();
			}
			clock[ANIMADELAY].restart();
		}
		anima.img.move(this->id / abs(this->id) * this->spd, 0);
		if (anima.getFrames() == anima.getNoOfFrames("f1") - 1) { 
			walkAnima = true;
		}
		else if (anima.getFrames() == 0) {
			walkAnima = false;
		}
	}
	bool attack() {
		if (clock[ANIMADELAY].getElapsedTime().asMilliseconds() >= delay) {
			anima.rectChange(1, anima.getNoOfFrames("f2"));
			anima.incrementFrames();
			clock[ANIMADELAY].restart();
		}
		if (anima.getFrames() == anima.getNoOfFrames("f2")) {
			anima.setFrames(0);
			return true;
		}
		else return false;
	}
	void reset() {
		clock[ANIMADELAY].restart();
		anima.setFrames(0);
	}
	virtual bool die() {
		int top = 2;
		if (clock[ANIMADELAY].getElapsedTime().asMilliseconds() >= delay) {
			anima.rectChange(top, anima.getNoOfFrames("f3"));
			anima.incrementFrames();
			clock[ANIMADELAY].restart();
		}
		if (anima.getFrames() >= anima.getNoOfFrames("f3") - 1) {
			anima.setFrames(0);
			return true;
		}
		else return false;
	}
	bool isPushed() {
		return beingPushed;
	}
	void push(bool cond) {
		beingPushed = cond;
	}
	int getAtkValue() {
		return this->atk;
	}
	void setAtkValue(int a) {
		this->atk = a;
	}
	virtual void draw() {
		anima.ptrWindow->draw(rangeCircle.getCircle());
		anima.img.setTextureRect(*anima.getRect());
		anima.ptrWindow->draw(hitbox.getBar()); //draws hitbox
		if (!dead)
			anima.ptrWindow->draw(hpBar.getBar());
		anima.ptrWindow->draw(*anima.img.getSprite()); //draws sprite
	}
	std::shared_ptr<troop> getEnemyInstance() {
		if (ptr != nullptr) {
			return ptr;
		}
	}
	void kill() {
			this->dead = true;
			this->isAtk = false;
			this->move = false;
			this->reset();
	}
	bool outOfBounds() {
		if (anima.img.getPosition().x > 2000 || anima.img.getPosition().x < -2000 || anima.img.getPosition().y > 1000 || anima.img.getPosition().y < -1000)
		{
			return true;
		}
		else return false;
	}
	virtual void focus(shared_ptr<troop> a) = 0;

	virtual void unfocus() {
		nullInstance();
		if (!isPushed())
			setMove(true);
		setAttack(false);
	}
	void operator*(float a) {
		this->maxHp *= a;
		this->health = maxHp;
		this->atk *= a;
	}
	void scaleOptimize(int a) {
		if (anima.getScaleFactor() != a) {
			anima.setScaleFactor(a);
			anima.img.scale(-1, 1);
		}
	}
	void update() {
		if (outOfBounds()) 
			remove = true;
		if (id > 0) {
			scaleOptimize(1);
		}
		else {
			scaleOptimize(-1);
		}
			if (beingPushed) 
			{
				anima.img.move(-1 * 25/weight, 0);
				if (clock[PUSH].getElapsedTime().asMilliseconds() >= (1000 - weight*4)) {
					move = true;
					beingPushed = false;
					clock[PUSH].restart();
				}
			}
			if (this->move) {
				walk();
			}
			else if (this->isAtk) {
				if (ptr != nullptr) {
					if (hitbox.getPosition().x > ptr->hitbox.getPosition().x)//if image is ahead
					{
						if (id > 0) { //if its allies' images that are ahead then we flip them to -x axis
							scaleOptimize(-1);
						}
						else {// images are already flipped in the ahead condition. we check if its flipped the wrong way or not. if it is then we flip it the right way which is towards -x axis
							if (anima.getScaleFactor() == 1) {
								anima.setScaleFactor(-1);
								anima.img.scale(anima.getScaleFactor(), 1);
							}
						}
					}


					else if (hitbox.getPosition().x < ptr->hitbox.getPosition().x)// behind condition
					{
						if (id < 0) {//if its enemies' images that are behind then we flip them to +x axis
							scaleOptimize(1);
						}
						else {// for allies, images are not flipped/ are towards x axis in the behind condition. we check if its flipped the wrong way or not. if it is then we flip it the right way which is towards +x axis
							if (anima.getScaleFactor() == -1) {
								anima.setScaleFactor(1);
								anima.img.scale(-1, 1);
							}
						}
					}
				}
				if (clock[ATTACKSPEED].getElapsedTime().asMilliseconds() >= attackSpd) {
					if (this->attack())
					{
						this->damage();
						clock[ATTACKSPEED].restart();
					}
				}
				if (ptr != nullptr) {
					if (this->isEnemyDead() || ptr->id / abs(ptr->id) == id / abs(id)) { // This stops them from attacking each other if they are in same vector
						this->isAtk = false; // ^^^^^^This condition comes because of howl
						this->move = true;
						ptr = nullptr;
						anima.setFrames(0);
					}
				}
			}
			if (!dead) {
				if (health <= 0) {
					kill();
				}
			}
			if (dead) {
				if (die()) {
					this->remove = true;
				}
			}
			hitbox.update();
			hpBar.update();
			rangeCircle.update();
			effectWearOff();
		}
};
