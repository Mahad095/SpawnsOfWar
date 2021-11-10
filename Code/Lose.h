#pragma once
#include "state.h"
class Lose :
    public State
{
    image lose, back, restart;
public:
    Lose(States& b, InputState& c) : State(game::get(), b, c)
    {
        lose.createImage("interface", "lose", "sprites\\GUI\\you_lose2.png", true);
        lose.centerImage(gameInstance.window.getSize());

        back.createImage("interface", "backBtn", "sprites\\GUI\\prev.png", true);
        back.setPosition(gameInstance.window.getSize().x - (1.f / 10.f) * gameInstance.window.getSize().x, (1.f / 30.f) * gameInstance.window.getSize().x);

        restart.createImage("interface", "resetBtn", "sprites\\GUI\\restart.png", true);
        restart.setPosition(460 , 350);
        Clickables.push_back(restart.getSprite());
        Clickables.push_back(back.getSprite());
    }
    void draw()
    {
        gameInstance.window.draw(lose);
        gameInstance.window.draw(back);
        gameInstance.window.draw(restart);
    }
    void handleEvents()
    {
        if (back.contains(Vector2f(gameInstance.mouseCoordinates))) {
            *state = WAVES;
        }
        if (restart.contains(Vector2f(gameInstance.mouseCoordinates)))
        {
            gameInstance.initWave();
            *state = GAME;
            gameInstance.gameStart = true;
        }
    }
};

