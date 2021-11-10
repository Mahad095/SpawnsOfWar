#pragma once
#include"buildings.h"
#include"global.h"
using namespace std;
class Castle:public building
{
	image img[3];
public:
	~Castle() {	}
	 Castle(RenderWindow* window) {
		 img[0].createImage("building", "castle", "sprites\\Castle\\castle1.png", true);
		img[1].createImage("building", "brokenCastle", "sprites\\Castle\\castle2.png", true);
		img[2].createImage("building", "fullBrokenCastle", "sprites\\Castle\\castle3.png", true);
		ptrWindow = window;
		for (size_t i = 0; i < 3; i++)
		{
			img[i].setPosition(-1 * (float(ptrWindow->getSize().x / 6)), 3 * (float(ptrWindow->getSize().y / 4)) - (float(img[i].getSize().y)));

		}		
		hp = 5000;
		maxHp = hp;
		hitbox.set(&hp, &img[0], 400, 200, 50);
		hpbar.set(&hp, &maxHp, &hitbox, 100, 20);
	}
	 bool isCastleDestroyed() {
		 if (hp <= 0) return true;
		 else return false;
	 }
	 void init() {
		 hp = maxHp;
		 for (size_t i = 0; i < 3; i++)
		 {
			 img[i].setPosition(-1 * (float(ptrWindow->getSize().x / 6)), 3 * (float(ptrWindow->getSize().y / 4)) - (float(img[i].getSize().y)));

		 }
	 }
	 void draw() {
		 ptrWindow->draw(hitbox.getBar());
		 if (hp >= (66.f / 100.f) * maxHp) {
			 ptrWindow->draw(*img[0].getSprite());
		 }
		 else if (hp >= (33.f / 100.f) * maxHp && hp < (66.f / 100.f) * maxHp)
		 {
			 ptrWindow->draw(*img[1].getSprite());
		 }
		 else if (hp >= 0 && hp < (33.f / 100.f) * maxHp)
		 {
			 ptrWindow->draw(*img[2].getSprite());
		 }
		 ptrWindow->draw(hpbar.getBar());
	 }	
	 void updatePosition() {
		 for (size_t i = 0; i < 3; i++)
		 {
			 img[i].move(global::windowOffset, 0);
		 }
	 }
};

