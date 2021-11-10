#pragma once
#include"troop1.h"
#include<time.h>
enum enemyTags {
	DEMONKING,
	FALLENANGEL,
	HOWL,
	OGRE,
	VAMPIRE
};
struct Enemies{
	string name;
	int manaPrice;
};
class EnemySpawner
{
	Enemies EnemyInfo[5] = { {"demonKing",100}, {"fallenAngel", 100}, {"Howl", 20}, {"Ogre", 15}, {"vampire", 100} };
	int waves;
	std::vector<shared_ptr<troop>>* enemies;
	std::vector<shared_ptr<projectile>>* projectiles;
	float weightSum;
	StoppableClock clock;
	float value;
	float max;
	RenderWindow* ptrWindow;
	bool isBossSpawned;
	shared_ptr<troop> boss;
public:
	EnemySpawner(std::vector<shared_ptr<projectile>>& list1, std::vector<shared_ptr<troop>>& list2, RenderWindow* window) {
		waves = 1;
		projectiles = &list1;
		enemies = &list2;
		weightSum = 0;
		value = 0.1;
		max = 200;
		ptrWindow = window;
		isBossSpawned = false;
	}
	void update() {
		if (weightSum > max) weightSum = max;
		if (!isBossSpawned) {
			switch (waves) {
			case 1:
				spawnBoss(VAMPIRE);
				break;
			case 2:
				spawnBoss(FALLENANGEL);
				break;
			case 3:
				spawnBoss(DEMONKING);
				break;
			}
		}
		if (boss->isRemove()) {
			killBoss();
			return;
		}
		weightSum += value;
		if (waves == 1) {
			if (clock.getElapsedTime().asMilliseconds() >= 2000) {
				if (rand() % 2 == 1) {
					spawnTroop(OGRE);
				}
				else
					spawnTroop(HOWL);
				clock.restart();
			}
		}
		if (waves == 2) {
			if (weightSum <= max / 2) {
				if (clock.getElapsedTime().asMilliseconds() >= 2000) {
					if (rand() % 2 == 1) {
						spawnTroop(OGRE);
					}
					else
						spawnTroop(HOWL);
					clock.restart();
				}
			}
			else {
				if (clock.getElapsedTime().asMilliseconds() >= 2000) {
					spawnTroop(VAMPIRE);
					clock.restart();
				}
			}
		}
		if (waves == 3) {
			if (weightSum <= max / 2) {
				if (clock.getElapsedTime().asMilliseconds() >= 2000) {
					if (rand() % 2 == 1) {
						spawnTroop(OGRE);
					}
					else
						spawnTroop(HOWL);
					clock.restart();
				}
			}
			else {
				if (clock.getElapsedTime().asMilliseconds() >= 2000) {
					if (rand() % 2 == 1) {
						spawnTroop(VAMPIRE);
					}
					else
						spawnTroop(FALLENANGEL);
					clock.restart();
				}
			}
		}
	}
	float& getWeight() {
		return weightSum;
	}

	void setIsBossSpawned(bool cond) {
		isBossSpawned = cond;
	}
	void spawnTroop(enemyTags a) {
		switch (a) {
		case OGRE:
			if (weightSum - EnemyInfo[OGRE].manaPrice >= 0) {
				enemies->push_back(std::shared_ptr<ogre>(new ogre(ptrWindow)));
				weightSum -= EnemyInfo[OGRE].manaPrice;
			}
			break;
		case HOWL:
			if (weightSum - EnemyInfo[HOWL].manaPrice >= 0) {
				enemies->push_back(std::shared_ptr<Howl>(new Howl(ptrWindow, *enemies)));
				weightSum -= EnemyInfo[HOWL].manaPrice;
			}
			break;
		case DEMONKING:
			if (weightSum - EnemyInfo[DEMONKING].manaPrice >= 0) {
				enemies->push_back(std::shared_ptr<demonKing>(new demonKing(ptrWindow, false)));
				weightSum -= EnemyInfo[DEMONKING].manaPrice;
			}
			break;
		case VAMPIRE:
			if (weightSum - EnemyInfo[VAMPIRE].manaPrice >= 0) {
				enemies->push_back(std::shared_ptr<vampire>(new vampire(ptrWindow, false)));
				weightSum -= EnemyInfo[VAMPIRE].manaPrice;
			}
			break;
		case FALLENANGEL:
			if (weightSum - EnemyInfo[FALLENANGEL].manaPrice >= 0) {
				enemies->push_back(std::shared_ptr<fallenAngel>(new fallenAngel(ptrWindow, projectiles, false)));
				weightSum -= EnemyInfo[FALLENANGEL].manaPrice;
			}
			break;
		}
	}
	void spawnBoss(enemyTags a) {
		isBossSpawned = true;
		switch (a) {
		case FALLENANGEL:
			boss = std::shared_ptr<fallenAngel>(new fallenAngel(ptrWindow, projectiles, true));
			break;
		case DEMONKING:
			boss = std::shared_ptr<demonKing>(new demonKing(ptrWindow, true));
			break;
		case VAMPIRE:
			boss = std::shared_ptr<vampire>(new vampire(ptrWindow, true));
			break;
		}
		enemies->push_back(boss);
	}
	int getWaveLevel() {
		return waves;
	}
	void setWaveLevel(int a) {
		waves = a;
	}
	void killBoss() {
		boss == nullptr;
		isBossSpawned = false;
	}
	bool isBossAlive() {
		if (boss->isRemove()) {
			killBoss();
			return false;
		}
		else return true;
	}
};