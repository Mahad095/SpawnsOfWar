#pragma once
#include "state.h"
class GameState :
    public State
{
    StoppableClock clocks[2], gameTimer;
    image troops[4], spells[2], dashboard, back;
    SurfaceText timer, manaTags[6];
    int seconds, minutes;
	void handleTimer() {
		if (gameTimer.getElapsedTime().asSeconds() >= 1) {
			if (seconds < 60) {
				seconds++;
			}
			else {
				minutes++;
				seconds = 0;
			}
			gameTimer.restart();
		}
		string s = to_string(seconds);
		if (seconds < 10) s = string("0") + s;
		string m = to_string(minutes);
		if (minutes < 10) m = string("0") + m;
		timer.setString(m + " " + s);
		timer.setPosition(timer.getPosition().x, timer.getPosition().y);
	}
public:
    GameState(States& b, InputState& c) : State(game::get(), b, c)
    {
		seconds = 0;
		minutes = 0;
        back.createImage("interface", "backBtn", "sprites\\GUI\\prev.png", true);
        back.setPosition(gameInstance.window.getSize().x - (1.f / 10.f) * gameInstance.window.getSize().x, (1.f / 30.f) * gameInstance.window.getSize().x);

		dashboard.createImage("interface", "dashboard", "sprites\\GUI\\dashboard.png", true);
		troops[0].createImage("troop", "knight", "sprites\\GUI\\knight1.png", true);
		troops[1].createImage("troop", "archer", "sprites\\GUI\\archer1.png", true);
		troops[2].createImage("troop", "wizard", "sprites\\GUI\\wizard1.png", true);
		troops[3].createImage("troop", "troll", "sprites\\GUI\\troll1.png", true);
		spells[0].createImage("spell", "heal", "sprites\\Spell\\heal.png", true);
		spells[1].createImage("spell", "barrageOfArrows", "sprites\\Spell\\barrageOfArrows.png", true);

		dashboard.setPosition(0, gameInstance.window.getSize().y - dashboard.getSize().y);
		for (size_t i = 0; i < 2; i++)
		{
			spells[i].setPosition((8 + i) * (gameInstance.window.getSize().x / 10) - 50, dashboard.getPosition().y + dashboard.getSize().y / 2 - spells[i].getSize().y / 2);
			Clickables.push_back(spells[i].getSprite());
		}

		for (size_t i = 0; i < 4; i++)
		{
			troops[i].setPosition((i + 1) * (gameInstance.window.getSize().x / 10) - 50, dashboard.getPosition().y + dashboard.getSize().y / 2 - troops[i].getSize().y / 2);
			Clickables.push_back(troops[i].getSprite());
		}

		for (size_t i = 0; i < 6; i++)
		{
			manaTags[i].set("sprites\\GUI\\tag1.png");
			if (i == 0)
				manaTags[i].setString(to_string(knight::manaPrice));
			else if (i == 1)
				manaTags[i].setString(to_string(archer::manaPrice));
			else if (i == 2)
				manaTags[i].setString(to_string(wizard::manaPrice));
			else if (i == 3)
				manaTags[i].setString(to_string(troll::manaPrice));
			else if (i == 4)
				manaTags[i].setString(to_string(heal::manaPrice));
			else if (i == 5)
				manaTags[i].setString(to_string(barrageOfArrows::manaPrice));
			manaTags[i].setSize(60, 30);
			manaTags[i].setCharacterSize(15);
			manaTags[i].setFillColor(Color(68, 30, 89));
			if (i < 4) {
				manaTags[i].setPosition(troops[i].getPosition().x + troops[i].getSize().x / 2 - manaTags[i].getSize().x / 2, troops[i].getPosition().y + troops[i].getSize().y - 20);
			}
			else if (i >= 4 && i <= 5) {
				manaTags[i].setPosition(spells[i - 4].getPosition().x + spells[i - 4].getSize().x / 2 - manaTags[i - 4].getSize().x / 2, spells[i - 4].getPosition().y + spells[i - 4].getSize().y);
			}
		}
		timer.set("sprites\\GUI\\tag1.png");
		timer.setSize(140, 70);
		timer.setCharacterSize(30);
		timer.setPosition(gameInstance.window.getSize().x / 2 - timer.getSize().x / 2, 20);
		Clickables.push_back(back.getSprite());
	}
    void draw()
    {
		handleTimer();
		gameInstance.window.draw(dashboard);

		for (size_t i = 0; i < 4; i++) gameInstance.window.draw(troops[i]);
		for (size_t i = 0; i < 2; i++) gameInstance.window.draw(spells[i]);
		for (size_t i = 0; i < 6; i++) gameInstance.window.draw(manaTags[i]);
		gameInstance.window.draw(timer);
		gameInstance.window.draw(back);
    }
	~GameState()
	{
		gameInstance.initWave();
		gameInstance.gameStart = false;
	}
    void handleEvents()
    {
		if (back.contains(Vector2f(gameInstance.mouseCoordinates))) {
			gameInstance.initWave();
			*state = WAVES;
			gameInstance.gameStart = false;
		}
		if (Spell::selected) {
			if (gameInstance.mouseCoordinates.y > 0 && gameInstance.mouseCoordinates.y < dashboard.getPosition().y) { //dashboard
				Spell::deployed = true;
				Spell::selected = false;
				if (gameInstance.spells[0]->getName() == "heal") {
					if (gameInstance.manaLevel - heal::manaPrice >= 0) {
						gameInstance.manaLevel -= heal::manaPrice;
						gameInstance.enemySpawner.getWeight() += heal::manaPrice;
					}
				}
				if (gameInstance.spells[0]->getName() == "barrageOfArrows") {
					if (gameInstance.manaLevel - barrageOfArrows::manaPrice >= 0) {
						gameInstance.manaLevel -= barrageOfArrows::manaPrice;
						gameInstance.enemySpawner.getWeight() += barrageOfArrows::manaPrice;
					}
				}
			}
			else {
				for (size_t i = 0; i < 2; i++)
				{
					if (spells[i].getGlobalBounds().contains(Vector2f(gameInstance.mouseCoordinates))) {
						Spell::deployed = false;
						Spell::selected = false;
						gameInstance.spells.erase(gameInstance.spells.begin() + 0);
					}
				}
			}
		}
		else if (!Spell::deployed) {            // troops !deployed
			for (size_t i = 0; i < 2; i++) //Deploying the Spells
			{
				if (spells[i].contains(Vector2f(gameInstance.mouseCoordinates))) {
					if (spells[i].getName() == "heal") {
						if (gameInstance.manaLevel - heal::manaPrice >= 0) {
							if (!Spell::selected) {
								Spell::selected = true;
								gameInstance.spells.push_back(std::shared_ptr<heal>(new heal(&gameInstance.window, gameInstance.allies, gameInstance.mouseCoordinates, gameInstance.particles)));
							}
						}
						else {
							gameInstance.errorMessages.push_back(shared_ptr<ErrorMessage>(new ErrorMessage(&gameInstance.window, "Not enough mana", 30)));
						}
					}
					else if (spells[i].getName() == "barrageOfArrows") {
						if (gameInstance.manaLevel - barrageOfArrows::manaPrice >= 0) {
							if (!Spell::selected) {
								Spell::selected = true;
								gameInstance.spells.push_back(std::shared_ptr<barrageOfArrows>(new barrageOfArrows(&gameInstance.window, gameInstance.mouseCoordinates, gameInstance.projectiles)));
							}
						}
						else {
							gameInstance.errorMessages.push_back(shared_ptr<ErrorMessage>(new ErrorMessage(&gameInstance.window, "Not enough mana", 30)));
						}
					}
				}
			}
		}
		if (!Spell::selected) {
			for (size_t i = 0; i < 4; i++) //Loop for spawning troops
			{
				if (troops[i].contains(Vector2f(gameInstance.mouseCoordinates))) {
					if (clocks[0].getElapsedTime().asMilliseconds() >= 500) { //delay in troop spawning
						clocks[0].restart();
						if (troops[i].getName() == "knight") {
							if (gameInstance.manaLevel - knight::manaPrice >= 0) {
								gameInstance.allies.push_back(std::shared_ptr<knight>(new knight(&gameInstance.window)));
								gameInstance.manaLevel -= knight::manaPrice;
								gameInstance.enemySpawner.getWeight() += knight::manaPrice;
							}
							else {
								gameInstance.errorMessages.push_back(shared_ptr<ErrorMessage>(new ErrorMessage(&gameInstance.window, "Not enough mana", 30)));
							}
						}
						if (troops[i].getName() == "archer") {
							if (gameInstance.manaLevel - archer::manaPrice >= 0) {
								gameInstance.allies.push_back(std::shared_ptr<archer>(new archer(&gameInstance.window, &gameInstance.projectiles)));
								gameInstance.manaLevel -= archer::manaPrice;
								gameInstance.enemySpawner.getWeight() += archer::manaPrice;
							}
							else {
								gameInstance.errorMessages.push_back(shared_ptr<ErrorMessage>(new ErrorMessage(&gameInstance.window, "Not enough mana", 30)));
							}
						}
						if (troops[i].getName() == "wizard") {
							if (gameInstance.manaLevel - wizard::manaPrice >= 0) {
								gameInstance.allies.push_back(std::shared_ptr<wizard>(new wizard(&gameInstance.window, &gameInstance.projectiles)));
								gameInstance.manaLevel -= wizard::manaPrice;
								gameInstance.enemySpawner.getWeight() += wizard::manaPrice;
							}
							else {
								gameInstance.errorMessages.push_back(shared_ptr<ErrorMessage>(new ErrorMessage(&gameInstance.window, "Not enough mana", 30)));
							}
						}
						if (troops[i].getName() == "troll") {
							if (gameInstance.manaLevel - troll::manaPrice >= 0) {
								gameInstance.allies.push_back(std::shared_ptr<troll>(new troll(&gameInstance.window)));
								gameInstance.manaLevel -= troll::manaPrice;
								gameInstance.enemySpawner.getWeight() += troll::manaPrice;
							}
							else {
								gameInstance.errorMessages.push_back(shared_ptr<ErrorMessage>(new ErrorMessage(&gameInstance.window, "Not enough mana", 30)));
							}
						}
					}
					else {
						gameInstance.errorMessages.push_back(shared_ptr<ErrorMessage>(new ErrorMessage(&gameInstance.window, "A troop was spawned recently", 30)));
					}
				}
			}
		}
    }

	void update()
	{
			if (!gameInstance.enemySpawner.isBossAlive()) {  //If boss dies/Player wins, then the player record is updated
				int total_seconds = (minutes * 60) + seconds;
				gameInstance.score += (1000 - total_seconds);
				if (gameInstance.player.score[gameInstance.enemySpawner.getWaveLevel() - 1] < gameInstance.score)
					gameInstance.player.score[gameInstance.enemySpawner.getWaveLevel() - 1] = gameInstance.score;
				*state = WIN;
				if (!gameInstance.turnMusicOff) {
					gameInstance.sounds[0].play();
				}
				if (gameInstance.enemySpawner.getWaveLevel() == gameInstance.player.waveLevel) {
					if (gameInstance.enemySpawner.getWaveLevel() + 1 <= 3) {
						gameInstance.player.waveLevel = gameInstance.enemySpawner.getWaveLevel() + 1;
					}
				}
				currentScore = gameInstance.score;
				gameInstance.fileRecords.update_record(gameInstance.player);
				gameInstance.initWave();
			}
			if (gameInstance.castle->isCastleDestroyed()) {
				gameInstance.initWave();
				*state = LOSE;
				if (!gameInstance.turnMusicOff)
					gameInstance.sounds[1].play();
			}
	}
};

