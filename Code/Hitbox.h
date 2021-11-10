#pragma once
#include"bars.h"
#include"image.h"
#include"global.h"
class Hitbox:public Bars
{
	image* ptrImg;
	float offsetY;
	int* id;
public:
	Hitbox(){
		this->setFillColor(Color::Transparent);
	}
	void set(int* e,image* a, float x, float y, float d) {
		bar.setSize(Vector2f(x, y));
		ptrImg = a;
		id = e;
		offsetY = d;
		update();
	}

	void update()
	{
		setPosition(ptrImg->getPosition().x + int(ptrImg->getWidth() / 2) - getSize().x / 2, ptrImg->getPosition().y + ptrImg->getHeight() / 2 - getSize().y / 2 + offsetY);
	}

	void setRotation(float f) {
		this->bar.setRotation(f);
	}
};

