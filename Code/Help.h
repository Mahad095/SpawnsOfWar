#pragma once
#include "state.h"
class Help :
    public State
{
    image pages[6], back;
    int pageNo;
    public:
        Help(States& b, InputState& c) : State(game::get(), b, c)
        {
            pageNo = 0;
            for (size_t i = 0; i < 6; i++)
            {
                string path = "sprites\\Help\\page1" + to_string(i + 1) + ".png";//page2,page2....6
                pages[i].createImage("interface", "helpSection", path, true);
                pages[i].centerImage(gameInstance.window.getSize());
            }
            back.createImage("interface", "backBtn", "sprites\\GUI\\prev.png", true);
            back.setPosition(gameInstance.window.getSize().x - (1.f / 10.f) * gameInstance.window.getSize().x, (1.f / 30.f) * gameInstance.window.getSize().x);
            Clickables.push_back(back.getSprite());
        }
        void takeInput(char a)
        {
            if (a == 'A')
            {
                if (pageNo > 0)
                    pageNo--;
            }
            else if (a == 'D'){
                if (pageNo < 5)
                    pageNo++;
            }
        }
        void draw()
        {
            gameInstance.window.draw(pages[pageNo]);
            gameInstance.window.draw(back);
        }
        void handleEvents()
        {
            if (back.contains(Vector2f(gameInstance.mouseCoordinates))) {
                *state = MENU;
            }
        }
};

