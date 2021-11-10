#pragma once
#include "state.h"
class Win :
    public State
{
	myText score;
	image stars[4], winBoard, back, next;
public:
    Win(States& b, InputState& c) : State(game::get(), b, c)
    {
		winBoard.createImage("interface", "win", "sprites\\GUI\\you_win2.png", true);
		winBoard.centerImage(gameInstance.window.getSize());

		score.setCharacterSize(40);
		score.setFillColor(Color(4, 126, 155));
		score.setString(to_string(currentScore));
		score.setPosition(gameInstance.window.getSize().x / 2 - score.getSize().x / 2, 350);

		back.createImage("interface", "backBtn", "sprites\\GUI\\prev.png", true);
		back.setPosition(gameInstance.window.getSize().x - (1.f / 10.f) * gameInstance.window.getSize().x, (1.f / 30.f) * gameInstance.window.getSize().x);

		next.createImage("interface", "nextBtn", "sprites\\GUI\\next.png", true);
		next.setPosition(gameInstance.window.getSize().x / 2 - next.getSize().x / 2, 450);

		for (size_t i = 0; i < 4; i++) {
			string tempPath = string("sprites\\GUI\\") + string("star_") + to_string(i + 1) + string(".png"); //star_1.png,star_2.png.....
			stars[i].createImage("score", "stars", tempPath, true);
			stars[i].setPosition(gameInstance.window.getSize().x / 2 - stars[i].getSize().x / 2, 150);
		}
		Clickables.push_back(back.getSprite());
		Clickables.push_back(next.getSprite());
    }
	void draw()
	{
		int ind = 0;
		gameInstance.window.draw(winBoard);
		gameInstance.window.draw(back);
		if (gameInstance.enemySpawner.getWaveLevel() < 3)
			gameInstance.window.draw(next);
		if (State::currentScore >= 1600) ind = 0;
		else if (State::currentScore >= 1400) ind = 1;
		else if (State::currentScore >= 1200) ind = 2;
		else ind = 3;
		gameInstance.window.draw(stars[ind]);
		gameInstance.window.draw(score);
	}
	void handleEvents()
	{
		if (back.contains(Vector2f(gameInstance.mouseCoordinates))) //back
		{
			*state = WAVES;
		}
		if (next.contains(Vector2f(gameInstance.mouseCoordinates)) && gameInstance.enemySpawner.getWaveLevel() < 3) //next
		{
			gameInstance.enemySpawner.setWaveLevel(gameInstance.enemySpawner.getWaveLevel() + 1); // Increasing level by 1
			gameInstance.initWave();
			*state = GAME;
			gameInstance.gameStart = true;
		}
	}
};

