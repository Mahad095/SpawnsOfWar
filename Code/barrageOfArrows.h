#pragma once
#include"Spell.h"
#include"arrow.h"
#include<time.h>
class barrageOfArrows :
    public Spell
{
    int numberOfArrows;
    int damage;
    int id;
    std::vector<std::shared_ptr<projectile>>* ptrProjectiles;
public:
    const static int manaPrice = 20;
    ~barrageOfArrows() {
    }
    barrageOfArrows(RenderWindow* window, Vector2i& mouse, std::vector<std::shared_ptr<projectile>>& list) {
        area = 500;
        overlay.createImage("overlay", "purpleOverlay", "sprites\\Spell\\purpleOverlay.png", true);
        overlay.getSprite()->setColor(Color(255, 255, 255, 100));
        ptrWindow = window;
        offset = 0;
        ptrMouse = &mouse;
        name = "barrageOfArrows";
        ptrProjectiles = &list;
        numberOfArrows = 35;
        damage = 50;
        id = 560;
        updateOverlay();
    }
    void update() {
        if (Spell::deployed) {
            for (size_t i = 0; i < numberOfArrows; i++)
            {   
                Vector2f start; 
                start.x = global::random(0, ptrWindow->getSize().x);
                start.y = 50;
                Vector2f end;
                end.x = global::random(overlay.getPosition().x, overlay.getPosition().x + overlay.getSize().x);
                end.y = 700;
                ptrProjectiles->push_back(std::shared_ptr<arrow>(new arrow(start,end,damage,ptrWindow,id)));
            }
            finishSpell();
        }
    }
    void updateOverlay() {
        overlay.setPosition(ptrMouse->x - float(overlay.getSize().x / 2), float(ptrWindow->getSize().y) - float(overlay.getTexture()->getSize().y) - float(ptrWindow->getSize().y / 4) + offset);
    }
};

