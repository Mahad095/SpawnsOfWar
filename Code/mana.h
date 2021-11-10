#pragma once
#include"bars.h"
#include"myText.h"
#include"SFML/Graphics.hpp"
using namespace sf;
class mana :public Bars, public myText
{
    image img;
    StoppableClock clock1;
    int* manaLevel;
public:
    mana() {
        myText::setCharacterSize(20);
        myText::setString("100");
        Bars::setFillColor(Color(7, 188, 224));
        Bars::setSize(265, 35);
        Bars::setPosition(100, 33);
        text.setPosition(35, 37);
        img.createImage("bar","manaBar","sprites\\GUI\\mana bar1.png",true);
        img.setPosition(5, 5);
    }
    void addMana(int a)
    {
        if (this->clock1.getElapsedTime().asMilliseconds() >= 1000) {
            if (*manaLevel < 100)
                *this->manaLevel += a;
            else if (*manaLevel + a >= 100) *manaLevel = 100;

            clock1.restart();
        }
    }
    void setManaPointer(int* a) {
        manaLevel = a;
    }
    void update() {
        this->addMana(5); //adds 5 mana
        float x = (float(*manaLevel) / float(100)) * 265;
        text.setString(to_string(*manaLevel));
        this->setSize(x, 35);
    }
    void draw(RenderWindow* window) {
        window->draw(*this->img.getSprite());
        window->draw(this->getBar());
        window->draw(text);
    }
};

