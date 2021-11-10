#pragma once
#include<SFML/Graphics.hpp>
#include"Hitbox.h"
#include"healthBar.h"
#include"image.h"
#include"global.h"
#include"RangeCircle.h"
using namespace sf;
using namespace std;
class animation {

	float offset;
	int f1, f2, f3;
	IntRect myRect;
	int frame;
	int* id;
	int scaleFactor;
public:
	RenderWindow* ptrWindow;
	image img;
	const float getOffset() {
		return offset;
	}
	void set(RenderWindow* window, String one, int a, int b, int c) {
		f1 = a; f2 = b; f3 = c; frame = 0;
		ptrWindow = window;
		img.createImage("troop","player", one, true);
		img.setPosition(-100.f, ptrWindow->getSize().y - img.getTexture()->getSize().y / 3 - ptrWindow->getSize().y / 4 + offset);
		rectChange(0, 10);
	}
	void setOffset(float a) 
	{
		this->offset = a;
	}
	IntRect* getRect() 
	{
		return &this->myRect;
	}
	void setScaleFactor(int i)
	{
		scaleFactor = i / abs(i);
	}
	int getScaleFactor() {
		return this->scaleFactor;
	}
	void setNoOfFrames(int a, int b, int c) {
		f1 = a;
		f2 = b;
		f3 = c;
	}
	int getNoOfFrames(std::string a) {
		if (a == "f1") return f1;
		else if (a == "f2") return f2;
		else if (a == "f3") return f3;
	}
	void rectChange(int topValue, int f) {
		myRect.width = img.getTexture()->getSize().x / f;
		myRect.height = img.getTexture()->getSize().y / 3;
		myRect.left = frame * myRect.width;
		myRect.top = topValue * img.getTexture()->getSize().y / 3;
		img.setTextureRect(myRect);
	}
	void setId(int& a) {
		this->id = &a;
	}
	void setFrames(int a) {
		this->frame = a;
	}
	int getFrames() {
		return this->frame;
	}
	void incrementFrames() {
		this->frame = frame + 1;
	}
	void decrementFrames() {
		this->frame = frame - 1;
	}
};