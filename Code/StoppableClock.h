#pragma once
#include"SFML/Graphics.hpp"
#include<vector>
using namespace sf;
class StoppableClock
{
	Clock clock;
	bool isPaused;
	Time elapsed, delta;
public:
	StoppableClock() {
		elapsed = milliseconds(0);
		isPaused = false;
	}
	void pause() {
		if (!isPaused) {
			elapsed = clock.getElapsedTime();
			isPaused = true;
		}
	}
	void unPause() {
		if (isPaused) {
			delta = clock.getElapsedTime() - elapsed;
			isPaused = false;
		}
	}
	Time getElapsedTime() {
		if (isPaused)
			return elapsed;
		else {
			Time t = clock.getElapsedTime() - delta;
			return t;
		}
	}
	void restart() {
		delta = milliseconds(0);
		elapsed = milliseconds(0);
		clock.restart();
	}
};


