#pragma once
#include"SurfaceText.h"
#include"game.h"
#include"myText.h"
#include"textField.h"
class State
{
protected:
	sf::Cursor cursor;
	std::vector<Sprite*>Clickables;
	States* state;
	game& gameInstance;
	InputState* inputState;
	static int currentScore;
public:
	State(game& a, States& b, InputState& c) : gameInstance(a), state(&b), inputState(&c){

	}
	~State()
	{
	}
	virtual void draw() = 0;
	virtual void handleEvents() = 0;
	virtual void takeInput(char){}
	virtual void update(){}
	void changeMouseIcon()
	{
		if (cursor.loadFromSystem(sf::Cursor::Arrow))
			gameInstance.window.setMouseCursor(cursor);

		for (size_t i = 0; i < Clickables.size(); i++)
		{
			if (Clickables[i]->getGlobalBounds().contains(Vector2f(gameInstance.mouseCoordinates))) {
				if (cursor.loadFromSystem(sf::Cursor::Hand))
					gameInstance.window.setMouseCursor(cursor);
			}
		}
	}

};

