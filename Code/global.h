#pragma once
#include"SFML/Graphics.hpp"
class global {
public:
	static float windowOffset;
	static float originX;

	static int random(int from, int to) {
		return rand() % (to - from + 1) + from;
	}
};
struct Record {
	std::string name;
	std::string password;
	int waveLevel;
	int score[3];
	int sum;
	Record() {
		init();
	}
	void init() {
		waveLevel = 1;
		score[0] = 0;
		score[1] = 0;
		score[2] = 0;
		sum = 0;
	}
	bool operator<(const Record& a) const
	{
		return sum > a.sum;
	}

};

enum States {
	MENU, 
	LEADERBOARD,
	WAVES,
	GAME,
	HELP,
	WIN,
	LOSE, //done
	INPUTSTATE //done
};
enum InputState {
	NEWGAME, LOADGAME
};