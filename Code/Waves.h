#pragma once
#include "state.h"
class Waves :
    public State
{
	image header, waveBoard, lock[2], logOut;
	SurfaceText waves[3];
	myText wavePlayerScores[3];
public:
	~Waves()
	{
	}
    Waves(States& b, InputState& c) : State(game::get(), b, c)
    {
		for (size_t i = 0; i < 3; i++)
		{
			waves[i].set("sprites\\GUI\\four.png");
			waves[i].setCharacterSize(50);
			waves[i].setFillColor(sf::Color(255, 207, 64));
			waves[i].setString(to_string(i + 1));
			waves[i].setSize(200, 200);
			waves[i].setPosition((i + 1) * 210 - 40, gameInstance.window.getSize().y / 2 - waves[i].getSize().y / 2);
			Clickables.push_back(waves[i].getSprite());
		}
											//putting wave scores on waves
		for (size_t i = 0; i < 3 ; i++) {
			wavePlayerScores[i].setCharacterSize(25);
			wavePlayerScores[i].setFillColor(sf::Color(255, 207, 64));
		
			wavePlayerScores[i].setString(to_string(gameInstance.player.score[i]));
			wavePlayerScores[i].setPosition(waves[i].getPosition().x + waves[i].getSize().x / 2 - wavePlayerScores[i].getSize().x/2, gameInstance.window.getSize().y / 2 - waves[i].getSize().y / 2 + 150);
		}

		header.createImage("interface", "board", "sprites\\GUI\\header1.png", true);
		header.setPosition(gameInstance.window.getSize().x / 2 - header.getSize().x / 2, 50);

		waveBoard.createImage("interface", "waveBoard", "sprites\\GUI\\two1.png", true);
		waveBoard.setPosition(gameInstance.window.getSize().x / 2 - waveBoard.getSize().x / 2, gameInstance.window.getSize().y / 2 - waveBoard.getSize().y / 2);
	
		for (size_t i = 0; i < 2; i++)
		{
			lock[i].createImage("interface", "lock", "sprites\\GUI\\lock.png", true);
			lock[i].setPosition(waves[i + 1].getPosition().x + waves[i + 1].getSize().x / 2 - lock[i].getSize().x / 2, waves[i + 1].getPosition().y + waves[i + 1].getSize().y / 2 - lock[i].getSize().y / 2);
		}

		logOut.createImage("interface", "logOutBtn", "sprites\\GUI\\logOut.png", true);
		logOut.setPosition(20, 20);
		Clickables.push_back(logOut.getSprite());
	}
    void draw()
    {
		gameInstance.window.draw(waveBoard);
		for (size_t i = 0; i < 3; i++)
		{
			gameInstance.window.draw(waves[i]);
		} 
		for (size_t i = 0; i < 3; i++)
		{
			gameInstance.window.draw(wavePlayerScores[i]);
		}
		if (gameInstance.player.waveLevel == 1) {
			this->gameInstance.window.draw(lock[0]);
			this->gameInstance.window.draw(lock[1]);
		}
		else if (gameInstance.player.waveLevel == 2) {
			this->gameInstance.window.draw(lock[1]);
		}
		gameInstance.window.draw(header);
		gameInstance.window.draw(logOut);
    }
    void handleEvents()
    {
		for (size_t i = 0; i < 3; i++)
		{
			if (waves[i].getSprite()->getGlobalBounds().contains(Vector2f(gameInstance.mouseCoordinates))) {
				if (gameInstance.player.waveLevel >= i + 1) {
					gameInstance.enemySpawner.setWaveLevel(i + 1); //The wave level is set here
					gameInstance.initWave();
					*state = GAME;
					gameInstance.gameStart = true;
				}
				else
				{
					gameInstance.errorMessages.push_back(shared_ptr<ErrorMessage>(new ErrorMessage(&gameInstance.window, "This level has not been unlocked yet", 30)));
				}
			}
		}
		if (logOut.contains(Vector2f(gameInstance.mouseCoordinates))) {
			//LogOut button
			*state = MENU;
		}
    }
};

