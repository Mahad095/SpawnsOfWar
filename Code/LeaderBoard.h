#pragma once
#include "state.h"
class LeaderBoard :
    public State
{
	image leaderBoardImg, back;
    myText highest;
	void formLeaderBoard() {
		vector<Record> tempRecords = gameInstance.fileRecords.get_All_Records(); //getting all the records

		for (size_t i = 0; i < tempRecords.size(); i++)
		{
			tempRecords[i].sum = tempRecords[i].score[0] + tempRecords[i].score[1] + tempRecords[i].score[2];
		}

		std::sort(tempRecords.begin(), tempRecords.end()); // sorting the records based on total 
		int least;
		if (tempRecords.size() == 0) {
			least = 0;
		}
		else if (tempRecords.size() < 10 && tempRecords.size() > 0) {
			least = tempRecords.size();
		}
		else least = 10;
		string tempStr;
		for (size_t i = 0; i < least; i++)
		{
			int val = 23 - tempRecords[i].name.length();
			tempStr += tempRecords[i].name + string(val, ' ') + to_string(tempRecords[i].sum) + '\n';

		}
		if (least == 0) highest.setString("No records to show");
		else highest.setString(tempStr);
		highest.setPosition(gameInstance.window.getSize().x / 2 - highest.getSize().x / 2, 150);
	}
public:
    LeaderBoard(States& b, InputState& c) : State(game::get(), b, c)
    {
        leaderBoardImg.createImage("interface", "leaderBoard", "sprites\\GUI\\leaderBoard1.png", true);
        leaderBoardImg.centerImage(gameInstance.window.getSize());

		back.createImage("interface", "backBtn", "sprites\\GUI\\prev.png", true);
		back.setPosition(gameInstance.window.getSize().x - (1.f / 10.f) * gameInstance.window.getSize().x, (1.f / 30.f) * gameInstance.window.getSize().x);

        highest.setCharacterSize(20);
        highest.setFont("fonts\\Cousine-Regular.ttf");
        highest.setFillColor(Color::Black);
		highest.setLineSpacing(1.5);
		formLeaderBoard();
		Clickables.push_back(back.getSprite());
    }
    void draw() 
    {
        gameInstance.window.draw(leaderBoardImg);
		gameInstance.window.draw(back);
        gameInstance.window.draw(highest);
    }
    void handleEvents() 
    {
        if (back.contains(Vector2f(gameInstance.mouseCoordinates))) { //back
            *state = MENU;
        }
    }
};

