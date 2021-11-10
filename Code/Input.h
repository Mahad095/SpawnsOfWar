#pragma once
#include "state.h"
class Input :
    public State
{
	image okBtn, back, inputForm;
	TextField name, pass;
public:
    Input(States& b, InputState& c): State(game::get(), b, c)
    {
        inputForm.createImage("interface", "inputForm", "sprites\\GUI\\input.png", true);
        inputForm.centerImage(gameInstance.window.getSize());

        back.createImage("interface", "backBtn", "sprites\\GUI\\prev.png", true);
        back.setPosition(gameInstance.window.getSize().x - (1.f / 10.f) * gameInstance.window.getSize().x, (1.f / 30.f) * gameInstance.window.getSize().x);

        okBtn.createImage("interface", "okBtn", "sprites\\GUI\\ok.png", true);
        okBtn.setPosition(gameInstance.window.getSize().x / 2 - okBtn.getSize().x / 2 - 15, 375);

        name.setPlaceHolder("Enter your name: ");
        pass.setPlaceHolder("Enter your password: ");
        pass.setEncryption(true); //Password is now encrypted
        name.setPosition(375, 200);
        pass.setPosition(375, 325);
		Clickables.push_back(okBtn.getSprite());
    }
    void draw() {
        gameInstance.window.draw(inputForm);
		gameInstance.window.draw(back);
		gameInstance.window.draw(okBtn);
        gameInstance.window.draw(name);
        gameInstance.window.draw(pass);
    }
	void takeInput(char a) 
	{
		name.getCharacter(a);
		pass.getCharacter(a);
	}
    void handleEvents() {
		if (back.contains(Vector2f(gameInstance.mouseCoordinates))) { //back
			name.reset();
			pass.reset();
			*state = MENU;
		}
		if (name.contains(Vector2f(gameInstance.mouseCoordinates))) {
			name.setFocus(true);
			pass.setFocus(false);
		}
		else
		{
			name.setFocus(false);
		}

		if (pass.contains(Vector2f(gameInstance.mouseCoordinates))) {
			pass.setFocus(true);
			name.setFocus(false);
		}
		else
		{
			pass.setFocus(false);
		}

		if (okBtn.contains(Vector2f(gameInstance.mouseCoordinates))) { //okBtn
			if (name.getString().length() < 1 || pass.getString().length() < 1)
				gameInstance.errorMessages.push_back(shared_ptr<ErrorMessage>(new ErrorMessage(&gameInstance.window, "Atleast 2 characters required in both fields", 30)));

			else {
				if (*inputState == NEWGAME) { 
					gameInstance.player.name = name.getString();
					gameInstance.player.password = pass.getString();
					if (gameInstance.fileRecords.doesRecordExist(gameInstance.player.name)) {
						gameInstance.errorMessages.push_back(shared_ptr<ErrorMessage>(new ErrorMessage(&gameInstance.window, "This username already exists", 30)));
					}
					else {
						gameInstance.fileRecords.add_Record(gameInstance.player);
						*state = WAVES;
						gameInstance.enemySpawner.setWaveLevel(1);
						//Now all information of player has been set
					}
				}
				else if (*inputState == LOADGAME) {
					if (gameInstance.fileRecords.validate_Record(name.getString(), pass.getString())) {
						gameInstance.player = gameInstance.fileRecords.get_Record(name.getString());
						//All information of the player is loaded after validation
						*state = WAVES;
						gameInstance.enemySpawner.setWaveLevel(1);
					}
					else {
						gameInstance.errorMessages.push_back(shared_ptr<ErrorMessage>(new ErrorMessage(&gameInstance.window, "Invalid username or password", 30)));
					}
				}
				name.reset();
				pass.reset();
			}
		}
    }
	void update()
	{
		name.update();
		pass.update();
	}
};

