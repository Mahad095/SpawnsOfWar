#include "game.h"
#include"Interface.h"
using namespace sf;
using namespace std;

//Initializing all static variables here
bool Spell::deployed = false;
bool Spell::selected = false;

float global::windowOffset = 0;
float global::originX = 0;
game game::instance;

void game::init()
{	

	this->name = "Spawns of war!";
	this->video.width = 1000;
	this->video.height = 600;
	this->window.create(video, name,sf::Style::Close);
	this->window.setFramerateLimit(30);
	this->gameStart = false;
	srand((unsigned)time(NULL));
	scrollCount = -1;
}

void game::audioInit(std::string file, bool cond)
{
	if (cond) {
		if (!this->audio.openFromFile(file)) {
			std::cout << "Couldnt open music" << std::endl;
		}
		audio.play();
		audio.setVolume(75);
	}
}

game::game(): enemySpawner(projectiles, enemies, &window), fileRecords("saveFile\\playerData.txt"){
	this->init();
	this->backg.set(&window);
	audioInit("Sounds\\background.wav", true);
	buff[0].loadFromFile("Sounds\\gameWin.wav");
	buff[1].loadFromFile("Sounds\\gameLose.wav");
	sounds[0].setBuffer(buff[0]);
	sounds[1].setBuffer(buff[1]);
	manaLevel = 100;   //max limit for mana
	manaBar.setManaPointer(&this->manaLevel);
	interface = shared_ptr<Interface>(new Interface());
	castle =  shared_ptr<Castle>(new Castle(&window));
	score = 0;
	fileRecords.read_Records();
}

game::~game() {
	fileRecords.write_Records();
	interface = nullptr;
}
game& game::get()
{
	return instance;
}
const bool game::running()
{
	return this->window.isOpen();
}

void game::handleEvents()
{
	while (this->window.pollEvent(this->e)) {
		switch (this->e.type) {
		case Event::MouseMoved:
			mouseCoordinates = sf::Mouse::getPosition(window);
			interface->changeMouseCursor();
			for (auto x : spells) x->updateOverlay();
			break;
		case Event::Closed:
			window.close();
			break;
		case Event::KeyPressed:
			if (this->e.key.code == Keyboard::Escape) {
				window.close();
			}
			else if (gameStart) { //These only work if the game has started
				if (this->e.key.code == Keyboard::Right) {
					if (scrollCount != 0)
						scroll(-1);
				}
				else if (this->e.key.code == Keyboard::Left) {
					if (scrollCount != -1)
						scroll(1);
				}
				else if (this->e.key.code == Keyboard::K) {
					castle->setHp(0);
				}
			}
			else if (this->e.key.code == Keyboard::A && interface->getState() == HELP) {
				interface->handleCharacterEvent('A');
			}
			else if (this->e.key.code == Keyboard::D && interface->getState() == HELP) {
				interface->handleCharacterEvent('D');
			}

			break;
		case Event::MouseButtonPressed:
			mouseCoordinates = sf::Mouse::getPosition(window);
			interface->handleMouseEvents();
			//This will be removed from finished game as these are just for testing purposes
			for (auto ally : allies) {
				if (ally->hitbox.getBar().getGlobalBounds().contains(Vector2f(mouseCoordinates))) {
					ally->kill();
					break;
				}
			}
			for (auto enemy : enemies) {
				if (enemy->hitbox.getBar().getGlobalBounds().contains(Vector2f(mouseCoordinates))) {
					enemy->kill();
					break;
				}
			}
					break;
		case Event::TextEntered:
			interface->handleCharacterEvent(static_cast<char>(e.text.unicode));
					break;
		}
	}

}
void game::update() {
	this->handleEvents();
	this->manaBar.update();
	if (gameStart) {
		this->enemySpawner.update();
	}
	interface->update();
	this->collisionHandler();
	this->iterate(allies, &troop::update);
	this->iterate(enemies, &troop::update);
	this->iterate(projectiles, &projectile::update);
	this->iterate(spells, &Spell::update);
	castle->update();
	iterate(particles, &Particles::update);
	this->iterate(errorMessages, &ErrorMessage::update);
	this->removeFromLists();
}
void game::render() {
	// clearing the window
	this->window.clear();
	//drawing on the window              // IF game hasnt started
		this->backg.draw();		// then only main menu and background is drawn
		if (gameStart) {
			castle->draw();
			manaBar.draw(&window);
		}
		interface->draw();
		iterate(allies, &troop::draw);
		iterate(enemies, &troop::draw);
		this->iterate(spells, &Spell::draw);
		iterate(projectiles, &projectile::draw);
		iterate(errorMessages, &ErrorMessage::draw);
		iterate(particles, &Particles::draw);
		//Displaying everything on the window
	this->window.display();
}
void game::collisionHandler()
{
	for (auto ally : allies) {
		bool check = false; //we use this bool to check if in the whole iteration if it collided with any enemy or not
		//Collision loop for Allies
		for (auto enemy : enemies) {
			if (ally->rangeCircle.inRange(enemy->hitbox) && (!ally->isDead() && !enemy->isDead()))
			{
				ally->focus(enemy);
				check = true;
				break;
			}
		}
		if (!check && !ally->isDead()) { //If it didnt collide, then we make it unfocus from the previous focused enemy
			ally->unfocus();
		}
	}
	for (auto enemy : enemies) {
		bool check = false;
		for (auto ally : allies) {
			//Collision loop for Enemies
			if (enemy->rangeCircle.inRange(ally->hitbox) && (!ally->isDead() && !enemy->isDead())) 
			{ 	
				enemy->focus(ally);
				check = true;
				break;
			}
		}
		if (!check && !enemy->isDead()) {
			enemy->unfocus();
		}
	}
	for (auto enemy : enemies) { // Collision loop for enemies with castle
			if (enemy->rangeCircle.inRange(castle->hitbox) && !enemy->isDead()) {
				enemy->getBuilding(castle);
				enemy->setAttack(true);
				enemy->setMove(false);
		}
	}
	//Collision loop for projectiles from allies with enemies
	for (auto ptr : projectiles) {
		if (ptr->getId() < 0) continue;   //All the enemy projectiles are exluded
		for (auto enemy : enemies) {
			if (ptr->hitbox.getBar().getGlobalBounds().intersects(enemy->hitbox.getBar().getGlobalBounds())) {
				if (!ptr->isSplash()) {
					ptr->damage(enemy);
					ptr->setRemove(true);
				}
				else {
					for (auto enemy : enemies) {
						if (((enemy->hitbox.getPosition().x) < (ptr->hitbox.getPosition().x + ptr->getSplashRange() / 2)) && ((enemy->hitbox.getPosition().x) > (ptr->hitbox.getPosition().x - ptr->getSplashRange() / 2))) {   //basically the attack would damage all enemies inside the splashrange
							ptr->damage(enemy);
						}
					}
 //im only removing the projectile after its hit everything in its range  in splash case
					ptr->setRemove(true);
				}
			}
		}
	}
	//Collision loop for projectiles from enemies with allies
	for (auto ptr : projectiles) {    
		if (ptr->getId() > 0) continue;   //All the projectiles from allies are exluded
		for (auto ally : allies) {
			if (ptr->hitbox.getBar().getGlobalBounds().intersects(ally->hitbox.getBar().getGlobalBounds())) {
				if (!ptr->isSplash()) {
					ptr->damage(ally);
					ptr->setRemove(true);
				}
				else {
					for (auto ally : allies) {
						if (((ally->hitbox.getPosition().x) < (ptr->hitbox.getPosition().x + ptr->getSplashRange() / 2)) && ((ally->hitbox.getPosition().x) > (ptr->hitbox.getPosition().x - ptr->getSplashRange() / 2))) {   //basically the attack would damage all enemies inside the splashrange
							ptr->damage(ally);
						}
					}
					ptr->setRemove(true);
				}
			}
		}
	}
	for (auto ptr : projectiles) {
			if (ptr->getId() > 0) continue;   //All the projectiles from allies are exluded
			if (ptr->hitbox.getBar().getGlobalBounds().intersects(castle->hitbox.getBar().getGlobalBounds())) {
				castle->takeDamage(ptr->getDamage());
				ptr->setRemove(true);
			}
	}
}
void game::removeFromLists() {
	for (size_t i = 0; i < allies.size(); i++)
	{
		if (allies[i]->isRemove() || allies[i]->getId() < 0) {
			allies.erase(allies.begin() + i);
		}
	}
	for (size_t j = 0; j < enemies.size(); j++)
	{
		if (enemies[j]->isRemove()) {
			score += enemies[j]->getWeight();  //Adding the weight of enemy as score whenever one is killed
			enemies.erase(enemies.begin() + j);
		}
	}
	for (size_t k = 0; k < projectiles.size(); k++)
	{
		if (projectiles[k]->isRemove())
		{
			projectiles.erase(projectiles.begin() + k);
		}
	}
	for (size_t i = 0; i < spells.size(); i++)
	{
		if (spells[i]->isRemove())
		{
			spells.erase(spells.begin() + i);
		}
	}
	for (size_t i = 0; i < errorMessages.size(); i++)
	{
		if (errorMessages[i]->isRemove())
		{
			errorMessages.erase(errorMessages.begin() + i);
		}
	}
	for (size_t i = 0; i < particles.size(); i++)
	{
		if (particles[i]->isRemove()) 
		{
			particles.erase(particles.begin() + i);
		}
	}
}

void game::spawnTroops()
{

	if (this->e.key.code == Keyboard::Num0) {
		enemies.push_back(std::shared_ptr<ogre>(new ogre(&window)));
	}
	if (this->e.key.code == Keyboard::Num9) {
		enemies.push_back(std::shared_ptr<Howl>(new Howl(&window, enemies)));
	}
	if (this->e.key.code == Keyboard::Num8) {
		enemies.push_back(std::shared_ptr<demonKing>(new demonKing(&window, false)));
	}
	if (this->e.key.code == Keyboard::Num7) {
		enemies.push_back(std::shared_ptr<vampire>(new vampire(&window, false)));
	}
	if (this->e.key.code == Keyboard::Num6) {
		enemies.push_back(std::shared_ptr<fallenAngel>(new fallenAngel(&window,&projectiles, false)));
	}
}
void game::scroll(int i) {
	global::windowOffset = i * int(window.getSize().x);
	global::originX += global::windowOffset;
	iterate(allies, &troop::updatePosition);
	iterate(enemies, &troop::updatePosition);
	iterate(projectiles, &projectile::updatePosition);
	iterate(spells, &Spell::updatePosition);
	castle->updatePosition();
	iterate(particles, &Particles::updatePosition);
	if (i == 1) scrollCount--;
	if (i == -1) scrollCount++;
}
void game::initWave() {
	for (auto x : allies) x->setRemove(true);
	for (auto x : enemies) x->setRemove(true);
	for (auto x : projectiles) x->setRemove(true);
	for (auto x : spells) x->setRemove(true);
	Spell::selected = false;
	Spell::deployed = false;
	for (auto x : errorMessages) x->setRemove(true);
	enemySpawner.killBoss();
	castle->init();
	manaLevel = 100;
	gameStart = false;
	scrollCount = -1;
	global::originX = 0;
	score = 0;
}