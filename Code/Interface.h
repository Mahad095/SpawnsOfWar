#pragma once
#include"SurfaceText.h"
#include"game.h"
#include"myText.h"
#include"textField.h"
#include"Menu.h"
#include"LeaderBoard.h"
#include"Waves.h"
#include"GameState.h"
#include"Help.h"
#include"Win.h"
#include"Lose.h"
#include"Input.h"

int State::currentScore = 0;

using namespace sf;
class Interface
{
	States state, beforeState;
	game& gameInstance;
	shared_ptr<State> currentState;
	InputState inputState;
public:
	void changeState()
	{
		if (beforeState != state) { 
			currentState = nullptr;
			beforeState = state;
			switch (beforeState)
			{
			case MENU:
				currentState = shared_ptr<Menu>(new Menu(state, inputState));
				break;
			case LEADERBOARD:
				currentState = shared_ptr<LeaderBoard>(new LeaderBoard(state, inputState));
				break;
			case WAVES:
				currentState = shared_ptr<Waves>(new Waves(state, inputState));
				break;
			case GAME:
				currentState = shared_ptr<GameState>(new GameState(state, inputState));
				break;
			case HELP:
				currentState = shared_ptr<Help>(new Help(state, inputState));
				break;
			case WIN:
				currentState = shared_ptr<Win>(new Win(state, inputState));
				break;
			case LOSE:
				currentState = shared_ptr<Lose>(new Lose(state, inputState));
				break;
			case INPUTSTATE:
				currentState = shared_ptr<Input>(new Input(state, inputState));
				break;
			}
		}
	}
	~Interface() 
	{
		currentState = nullptr;
	}
	void handleCharacterEvent(char c) {
		currentState->takeInput(c);
	}
	States getState() {
		return state;
	}
	Interface() : gameInstance(game::get()){
		state = MENU;
		beforeState = MENU;
		currentState = shared_ptr<Menu>(new Menu(state, inputState)) ;
	}
	void draw()
	{
		currentState->draw();
	}
	void update()
	{
		changeState();
		if (state == MENU || state == INPUTSTATE || state == LEADERBOARD || state == HELP) {
			if (gameInstance.audio.getStatus() != 2 && !gameInstance.turnMusicOff) {
				gameInstance.audio.stop();
				gameInstance.audio.play();
			}
		}
		else gameInstance.audio.stop();
		currentState->update();
	}

	void handleMouseEvents()
	{
		currentState->handleEvents();
	}
	void changeMouseCursor()
	{
		currentState->changeMouseIcon();
	}
};