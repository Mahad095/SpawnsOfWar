#pragma once
#include<iostream>
#include<vector>
#include"knight.h"
#include"ogre.h"
#include "background.h"
#include<memory>
#include<time.h>
#include"SFML/Audio.hpp"
#include"mana.h"
#include"archer.h"
#include"projectile.h"
#include "Troop1.h"
#include"arrow.h"
#include"Howl.h"
#include"troll.h"
#include"heal.h"
#include"barrageOfArrows.h"
#include"wizard.h"
#include"Orb.h"
#include"global.h"
#include"castle.h"
#include"demonKing.h"
#include"fallenAngel.h"
#include"vampire.h"
#include"EnemySpawner.h"
#include"ErrorMessage.h"
#include"StoppableClock.h"
#include"myFile.h"
class Interface;
class game {
private:
	friend class Interface;
	friend class State;
	friend class Menu;
	friend class Input;
	friend class Waves;
	friend class Help;
	friend class Win;
	friend class LeaderBoard;
	friend class Lose;
	friend class GameState;
	std::string name;
	sf::RenderWindow window;
	sf::Event e;
	sf::VideoMode video;
	bool gameStart;
	Vector2i mouseCoordinates;
	background backg;
	std::vector<std::shared_ptr<troop>> allies;
	std::vector<std::shared_ptr<projectile>> projectiles;
	std::vector<std::shared_ptr<troop>> enemies;
	std::vector<std::shared_ptr<Spell>> spells;
	std::shared_ptr<Castle> castle;
	std::vector<std::shared_ptr<ErrorMessage>> errorMessages;
	std::vector<std::shared_ptr<Particles>> particles;
	int score;
	EnemySpawner enemySpawner;
	Record player;
	Music audio;
	SoundBuffer buff[2];
	Sound sounds[2];
	myFile fileRecords;
	bool turnMusicOff;
	int scrollCount;
	mana manaBar;
	shared_ptr<Interface> interface;
	int manaLevel;
	void init();
	void audioInit(std::string file, bool cond);
	void handleEvents();
	// game updating and drawing it
	void collisionHandler();
	void removeFromLists();
	void print(Vector2f);
	template<typename T, typename method>
	void iterate(std::vector<std::shared_ptr<T>>& t, method m)
	{
		for (size_t i = 0; i < t.size(); i++) {
			(*t[i].*m)();
		}
	}
	void spawnTroops();
	void scroll(int i);
	void initWave();
	game(); //Private constructor so that only a single instance is available
	game(const game&) = delete; //delete copy constructor so no copies are possible
	static game instance; //A single static instance of the game class
public:
	//constructor and destructor
	~game();
	static game& get();
	void update();
	void render();
	const bool running();
};