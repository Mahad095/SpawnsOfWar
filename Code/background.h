#pragma once
#include<SFML/Graphics.hpp>
#include"image.h"
using namespace sf;

class background {
private:
	RenderWindow* ptrWindow;
	image img;
	int i;
	void fitToScreen()
	{
		Vector2u bgSize = this->img.getSize();
		Vector2u windowSize = this->ptrWindow->getSize();
		float ScaleX = (float)windowSize.x / bgSize.x;
		float ScaleY = (float)windowSize.y / bgSize.y;
		this->img.getSprite()->setScale(ScaleX, ScaleY);
	}
public:
	background(): i(3){}
	void set(RenderWindow* window) {
		this->ptrWindow = window;
		img.createImage("backgrounds", "background", "sprites\\Backgrounds\\game_background_3.png", true);
		fitToScreen();
		img.setOrigin(0, 0);
	}
	void draw() {
		this->ptrWindow->draw(*img.getSprite());
	}
	void changeBackground()
	{
		if (i < 4) i++;
		else i = 1;
		string path = "sprites\\Backgrounds\\game_background_" + to_string(i) +".png";
		img.changeTexture(path);
	}
};