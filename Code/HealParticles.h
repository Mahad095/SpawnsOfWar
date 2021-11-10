#pragma once
#include"Particles.h"
#include"image.h"
#include"global.h"

class HealParticles:public Particles
{
	image leaf;
public:
	HealParticles(sf::RenderWindow& window, Vector2f init) {
		if((rand() % 5 + 1) % 2 == 1)
		leaf.createImage("particle", "leaf1", "sprites\\Spell\\leaf1.png", true);
		else
		leaf.createImage("particle", "leaf2", "sprites\\Spell\\leaf2.png", true);
		alpha = 255;
		scale = 1;
		ptrWindow = &window;
		spd.y = global::random(5, 7);
		initialCoordinates = init;
		leaf.getSprite()->setColor(sf::Color(255, 255, 255, alpha));
	}
	void updatePosition() {
		leaf.setPosition(leaf.getPosition().x + global::windowOffset, leaf.getPosition().y);
	}
	 void update() {
		if (scale > 0)
			scale -= 0.001;
		alpha -= 5;
		if (alpha <= 0) remove = true;
		leaf.scale(scale,scale);
		leaf.getSprite()->rotate(1.f);
		initialCoordinates.y += spd.y;
		leaf.setPosition(initialCoordinates.x, initialCoordinates.y);
		leaf.getSprite()->setColor(sf::Color(255, 255, 255, alpha));
	}
	 void draw() {
		 this->ptrWindow->draw(*leaf.getSprite());
	 }

};

