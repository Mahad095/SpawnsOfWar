#pragma once
#include"SFML/Graphics.hpp"
#include"image.h"
class Spell 
{
protected:
	image overlay;
	Vector2f start, end;
	float area;
	RenderWindow* ptrWindow;
	float offset;
	Vector2i* ptrMouse;
	bool remove;
	int count;
	string name;
public:
	static bool deployed;
	static bool selected;
	Spell() {
		offset = 0;
		ptrWindow = nullptr;
		remove = false;
	}
	std::string getName() {
		return name;
	}
	void incremementCount() {
		count++;
	}
	virtual void setRemove(bool cond) {
		remove = cond;
	}
	void finishSpell() {
		remove = true;
		deployed = false;
		selected = false;
	}
	bool isRemove() {
		return remove;
	}

	virtual void updateOverlay() = 0;

	virtual void draw() {
		if(!deployed)
			this->ptrWindow->draw(*overlay.getSprite());
	}
	virtual void update() {}

	virtual void updatePosition() {
		overlay.setPosition(overlay.getPosition().x + global::windowOffset, overlay.getPosition().y);
	}
};

