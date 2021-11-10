#pragma once
#include "Spell.h"
#include"troop1.h"
#include"HealParticles.h"
#include<vector>
class heal :
    public Spell
{
    std::vector<std::shared_ptr<troop>>* Allies;
    int value;
    int ticks;
    StoppableClock clock;
    std::vector <std::shared_ptr<Particles>>* particles;
public:
    const static int manaPrice = 20;
    ~heal() {
    }
    heal(RenderWindow* window, std::vector<std::shared_ptr<troop>>& list, Vector2i& mouse, std::vector <std::shared_ptr<Particles>>& list2) {
        area = 400;
        overlay.createImage("overlay", "greenOverlay","sprites\\Spell\\greenOverlay.png", true);
        overlay.getSprite()->setColor(Color(255, 255, 255, 100));
        ptrWindow = window;
        offset = 0;
        Allies = &list;
        particles = &list2;
        value = 50;
        ticks = 0;
        ptrMouse = &mouse;
        name = "heal";
        updateOverlay();
    }
    void updatePosition() {
        overlay.setPosition(overlay.getPosition().x + global::windowOffset, overlay.getPosition().y);
    }
    void update() {
        if (Spell::deployed) {
            if (!remove) {
                particles->push_back(std::shared_ptr<HealParticles>(new HealParticles(*ptrWindow, Vector2f(rand() % int(overlay.getPosition().x + overlay.getTexture()->getSize().x) + int(overlay.getPosition().x), ptrWindow->getSize().y / 4))));
                if (particles->size() >= 30)
                    particles->pop_back();
            }
            if (clock.getElapsedTime().asSeconds() > 0.6) {
                for (size_t i = 0; i < Allies->size(); i++)
                {
                    if (!(*Allies)[i]->isHealing()) {
                        if (overlay.getSprite()->getGlobalBounds().intersects((*Allies)[i]->hitbox.getBar().getGlobalBounds())) {
                            (*Allies)[i]->setHeal(true);
                        }
                    }
                    if ((*Allies)[i]->isHealing()) {
                        if ((*Allies)[i]->getHealth() + value <= (*Allies)[i]->getMaxHealth())
                            (*Allies)[i]->setHealth((*Allies)[i]->getHealth() + value);
                        else
                            (*Allies)[i]->setHealth((*Allies)[i]->getMaxHealth());
                    }
                }
                ticks++;
                clock.restart();
                if (ticks >= 8) {
                    for (size_t i = 0; i < Allies->size(); i++) {
                        (*Allies)[i]->setHeal(false);
                    }
                    finishSpell();
                    for (auto x : *particles) {
                        x->setRemove(true);
                    }
                }
            }
        }
    }
    void setRemove(bool cond) {
        if (cond == true) {
            remove = true;
            for (auto x : *particles) {
                x->setRemove(true);
            deployed = false;
            selected = false;
            }
        }
        else remove = false;
    }
    void updateOverlay() {
        overlay.setPosition(ptrMouse->x - float(overlay.getSize().x / 2), float(ptrWindow->getSize().y) - float(overlay.getTexture()->getSize().y) - float(ptrWindow->getSize().y / 4) + offset);
    }
};
//When i click spel, its overlay appears
//I will not be able to click any other buttons
// If i right click then the spell is removed from the thing 
//OtherWise if i click on the battle field the spell is cast. i.e deploy is turned true
