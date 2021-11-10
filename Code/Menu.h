#pragma once
#include "state.h"
class Menu :
    public State
{
	SurfaceText mainMenuBtns[4];
	image music, leaderBoardBtn, title, changeBg;
public:
    Menu(States& b, InputState& c): State(game::get(), b, c)
    {
		for (size_t i = 0; i < 4; i++)
		{
			mainMenuBtns[i].set("sprites\\GUI\\one.png");
			mainMenuBtns[i].setSize(200, 70);
			mainMenuBtns[i].setFillColor(sf::Color(255, 207, 64));
		}
		mainMenuBtns[0].setString("NEW GAME");
		mainMenuBtns[1].setString("LOAD GAME");
		mainMenuBtns[2].setString("HELP");
		mainMenuBtns[3].setString("EXIT");

		for (size_t i = 0; i < 4; i++)
		{
			mainMenuBtns[i].setPosition(gameInstance.window.getSize().x / 2 - mainMenuBtns[i].getSize().x / 2, (120 * i) + 140);
			Clickables.push_back(mainMenuBtns[i].getSprite());
		}
		music.createImage("interface", "musicBtn", "sprites\\GUI\\music.png", true);
		music.setPosition(10, 500);
		changeBg.createImage("interface", "changeBgBtn", "sprites\\GUI\\changeBg.png", true);
		changeBg.setPosition(110, 500);
		leaderBoardBtn.createImage("interface", "leaderBoard", "sprites\\GUI\\leaderBtn.png", true);
		leaderBoardBtn.setPosition(900, 500);
		title.createImage("interface", "title", "sprites\\GUI\\title1.png", true);
		title.setPosition(gameInstance.window.getSize().x / 2 - title.getSize().x / 2, gameInstance.window.getSize().y / 11);
		Clickables.push_back(music.getSprite());
		Clickables.push_back(changeBg.getSprite());
		Clickables.push_back(leaderBoardBtn.getSprite());
	}
    ~Menu(){}
	void draw() {
		gameInstance.window.draw(music);
		gameInstance.window.draw(changeBg);
		gameInstance.window.draw(leaderBoardBtn);
		gameInstance.window.draw(title);
		for (size_t i = 0; i < 4; i++) gameInstance.window.draw(mainMenuBtns[i]);
	}
	void handleEvents() {
		if (mainMenuBtns[0].contains(Vector2f(gameInstance.mouseCoordinates))) {
			*state = INPUTSTATE;
			*inputState = NEWGAME;
			gameInstance.player.init();
		}
		else if (mainMenuBtns[1].contains(Vector2f(gameInstance.mouseCoordinates))) {
			*state = INPUTSTATE;
			*inputState = LOADGAME;
			gameInstance.player.init();
		}
		else if (mainMenuBtns[2].contains(Vector2f(gameInstance.mouseCoordinates))) {
			*state = HELP;
		}
		else if (mainMenuBtns[3].contains(Vector2f(gameInstance.mouseCoordinates))) {
			gameInstance.window.close();
		}
		else if (music.getSprite()->getGlobalBounds().contains(Vector2f(gameInstance.mouseCoordinates))) {
			if (!gameInstance.turnMusicOff) {
				gameInstance.audio.pause();
				gameInstance.turnMusicOff = true;
				gameInstance.errorMessages.push_back(shared_ptr<ErrorMessage>(new ErrorMessage(&gameInstance.window, "Audio disabled", 30)));
			}
			else {
				gameInstance.audio.play();
				gameInstance.turnMusicOff = false;
				gameInstance.errorMessages.push_back(shared_ptr<ErrorMessage>(new ErrorMessage(&gameInstance.window, "Audio enabled", 30)));
			}
		}
		else if (leaderBoardBtn.getSprite()->getGlobalBounds().contains(Vector2f(gameInstance.mouseCoordinates))) {
			*state = LEADERBOARD;
		}
		else if (changeBg.contains(Vector2f(gameInstance.mouseCoordinates)))
		{
			gameInstance.backg.changeBackground();
		}
	}
};

