#include "Game.h"
#include "graphics.h"





void Game::spawnShredder(int size, int lines) //The function that spawns the enemies.
{
	if (enemies.size() != 0) { //When the game begins again, it is ensured that the enemies are destroyed before the new ones are created.
		for (int i = enemies.size() - 1; i >= 0; i--) {
			delete enemies[i];
			enemies[i] == nullptr;
		}
		enemies.clear();
	}
	active_enemies = size * lines; //lines defines how many lines of enemies exist and size determines how many enemies exist in each line. 
	enemies_remaining = active_enemies;
	for (int j = 0; j < lines; j++) { //For all the lines of enemies
		for (int i = 0; i < size; i++) { ///For all the enemies in each line
			enemies.push_back(new Enemy(*this, BOX_LEFT+28 +65*i,15+ 65 * (j + 1))); //Appending the vector of active enemies to add one after the other.
				
		}
	}
	int maxStep = ((BOX_RIGHT - (BOX_LEFT + 28 + 55 * size  +20 )) / 20); //The max step defines how many steps the enemy can make before changing direction. 
	for (int k = 0; k < active_enemies; k++) { //Updates the max step of all the enemies. 
		enemies[k]->setMaxStep(maxStep);
	}
}

void Game::spawnBoxes(int box) //The function that spawns the boxes. 
{
	if (Shelter.size() != 0) { //When the game begins again, it is ensured that the boxes are destroyed before the new ones are created.
		for (int i = Shelter.size() - 1; i >= 0; i--) {
			delete Shelter[i];
			Shelter[i] == nullptr;
		}
		Shelter.clear();
	}
	this->boxes = box;
	float vspace = (float)800 / (box + 1); //The inbetween space from the one box to the other. 
	for (int i = 1; i <= box; i++) {
		Shelter.push_back(new Box(*this, (float)BOX_LEFT + i*vspace, (float)BOX_BOTTOM - 150)); //Appending the vector of active boxes to add one after the other.
	}
}

void Game::drawMenuScreen() //Draws everything related to the Menu Screen 
{
	this->init();
	graphics::Brush br;
	br.fill_color[0] = 0.2f;
	br.fill_color[1] = 0.1f;
	br.fill_color[2] = 0.8f;
	br.fill_secondary_color[0] = 0.5f;
	br.fill_secondary_color[1] = 0.2f;
	br.fill_secondary_color[2] = 0.7f;
	br.gradient = true;
	char info[40];
	sprintf_s(info, "The Charismatic Defenders");
	graphics::drawText(200, 350, 65, info, br);
	sprintf_s(info, "Press ENTER to start");
	graphics::drawText(400, 400, 45, info, br);
}
void Game::drawSelectionScreen() //Draws everything related to the Selection Screen 
{
	this->init();
	graphics::Brush br;
	br.fill_color[0] = 0.2f;
	br.fill_color[1] = 0.1f;
	br.fill_color[2] = 0.8f;
	br.fill_secondary_color[0] = 0.5f;
	br.fill_secondary_color[1] = 0.2f;
	br.fill_secondary_color[2] = 0.7f;
	br.gradient = true;
	char phrase[50];
	graphics::Brush b;
	b.fill_color[0] = 0.2f;
	b.fill_color[1] = 0.1f;
	b.fill_color[2] = 0.8f;
	b.fill_secondary_color[0] = 0.1f;
	b.fill_secondary_color[1] = 0.8f;
	b.fill_secondary_color[2] = 0.7f;
	b.gradient = true;

	sprintf_s(phrase, "Choose your character");
	graphics::drawText(330, 150, 55, phrase, br);

	graphics::setOrientation(0);
	graphics::Brush bru;
	bru.outline_opacity = 0.0f;

	//Pictures of the available characters, followed by bried descriptions of their abilities. 

	bru.texture = std::string(ASSET_PATH) + "KontonSprite.png";
	graphics::drawRect(300, 400, 256, 256, bru);
	sprintf_s(phrase, "Konton The Bard");
	graphics::drawText(220, 550, 25, phrase, b);
	graphics::drawText(225, 580, 15, "Attacks with music notes", b);
	graphics::drawText(225, 595, 15, "Oneshots enemies", b);
	graphics::drawText(225, 610, 15, "Slower attacks", b);

	bru.texture = std::string(ASSET_PATH) + "YuvoSprite.png";
	graphics::drawRect(600, 400, 256, 256, bru);
	sprintf_s(phrase, "Yuvo The Warlock");
	graphics::drawText(510, 550, 25, phrase, b);
	graphics::drawText(515, 580, 15, "Attacks with a blast of energy", b);
	graphics::drawText(515, 595, 15, "Hits two enemies at once", b);
	graphics::drawText(515, 610, 15, "Less Damage", b);

	bru.texture = std::string(ASSET_PATH) + "KlausSprite.png";
	graphics::drawRect(900, 400, 256, 256, bru);
	sprintf_s(phrase, "Klaus The Sorcerer");
	graphics::drawText(810, 550, 25, phrase, b);
	graphics::drawText(815, 580, 15, "Attacks with magic missiles", b);
	graphics::drawText(815, 595, 15, "Brings enemies to half life", b);
	graphics::drawText(815, 610, 15, "Faster attacks", b);

}
void Game::drawGameScreen() //Draws everything related to the Main Game Screen 
{
	//playing box
	graphics::Brush bro;
	bro.fill_color[0] = 0.1f;
	bro.fill_color[1] = 0.5f;
	bro.fill_color[2] = 0.9f;
	bro.fill_secondary_color[0] = 0.3f;
	bro.fill_secondary_color[1] = 0.1f;
	bro.fill_secondary_color[2] = 0.0f;

	bro.gradient = true;
	bro.gradient_dir_v = 1.0f;
	bro.outline_color[0] = 0.0f;
	bro.outline_color[1] = 0.18f;
	bro.outline_color[2] = 0.33f;
	bro.texture = std::string(ASSET_PATH) + "Cobbles.png";
	graphics::drawRect(600, WINDOW_HEIGHT / 2 + 25, CANVAS_WIDTH, 700, bro);


	if (this->player) { //This is where the main draw function of the player is called if the player exists
		this->player->draw();
	}
	if (!enemies.empty()) { //Same for the enemies
		for (int i = 0; i < active_enemies; i++) {
			if (this->enemies[i]->isActive()) {
				enemies[i]->draw();
			}
		}
	}

	if (!Shelter.empty()) { //And the boxes
		for (int i = 0; i < Shelter.size(); i++) {
			if (this->Shelter[i]->getHp() > 0.0f) {
				this->Shelter[i]->draw();
			}
		}
	}
	graphics::Brush Livebrush;
	graphics::setFont(std::string(ASSET_PATH) + "ARCADECLASSIC.ttf"); 
	Livebrush.fill_color[0] = 0.2f;
	Livebrush.fill_color[1] = 0.1f;
	Livebrush.fill_color[2] = 0.8f;
	Livebrush.fill_secondary_color[0] = 0.5f;
	Livebrush.fill_secondary_color[1] = 0.2f;
	Livebrush.fill_secondary_color[2] = 0.7f;
	Livebrush.gradient = true;
	graphics::drawText(BOX_LEFT + 5, BOX_BOTTOM + 40, 40, "LIVES", Livebrush); 
	graphics::drawText(BOX_RIGHT-150, BOX_BOTTOM +40, 40, "SCORE " + std::to_string(score), Livebrush); //Shows the score of the player
	if (this->player) {
		for (float i = 0.0f; i < this->player->getHp(); i++) { //Depending on the remaining lives of the player, small images of the selected player will be drawn to represent their number of lives.
			graphics::Brush livedraw;
			livedraw.outline_opacity = 0.0f;
			if (this->player->getCharacter() == 0) {
				livedraw.texture = std::string(ASSET_PATH) + "Konton.png";
			}
			else if (this->player->getCharacter() == 1) {
				livedraw.texture = std::string(ASSET_PATH) + "Yuvo.png";
			}
			else if (this->player->getCharacter() == 2) {
				livedraw.texture = std::string(ASSET_PATH) + "Klaus.png";
			}
			graphics::drawRect(BOX_LEFT + 150 + ((int)i) * 45, BOX_BOTTOM + 25, 45, 45, livedraw);
		}
	}

}
void Game::drawVictoryScreen() //Draws everything related to the Victory Screen 
{
	this->init();
	graphics::Brush br;
	br.fill_color[0] = 0.2f;
	br.fill_color[1] = 0.1f;
	br.fill_color[2] = 0.8f;
	br.fill_secondary_color[0] = 0.5f;
	br.fill_secondary_color[1] = 0.2f;
	br.fill_secondary_color[2] = 0.7f;
	br.gradient = true;
	char phrase[50];
	sprintf_s(phrase, "VICTORY");
	graphics::drawText(WINDOW_WIDTH/2 -78, 350, 75, phrase, br);
	sprintf_s(phrase, "Press ESCAPE to leave");
	graphics::drawText(400, 450, 45, phrase, br);
	sprintf_s(phrase, "Press SPACE to replay");
	graphics::drawText(400, 500, 45, phrase, br);
	graphics::drawText(540, 550, 45,"Score " + std::to_string(score), br);
	graphics::drawText(400, 800, 20, "Art by Giannis Glezos and Electra Papadopoulou", br);
}
void Game::drawLossScreen() //Draws everything related to the Loss Screen 
{
	this->init();
	graphics::Brush br;
	br.fill_color[0] = 0.2f;
	br.fill_color[1] = 0.1f;
	br.fill_color[2] = 0.8f;
	br.fill_secondary_color[0] = 0.5f;
	br.fill_secondary_color[1] = 0.2f;
	br.fill_secondary_color[2] = 0.7f;
	br.gradient = true;
	char phrase[50];
	sprintf_s(phrase, "DEFEAT");
	graphics::drawText(WINDOW_WIDTH / 2 - 55, 350, 75, phrase, br);
	sprintf_s(phrase, "Press ESCAPE to leave");
	graphics::drawText(400, 450, 45, phrase, br);
	sprintf_s(phrase, "Press SPACE to replay");
	graphics::drawText(400, 500, 45, phrase, br);
	graphics::drawText(540, 550, 45, "Score " + std::to_string(score), br);
	graphics::drawText(400, 800, 20, "Art by Giannis Glezos and Electra Papadopoulou", br);
}
void Game::updateMenuScreen(float ms) //The update function of the Menu Screen 
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) { //The only thing one can do in here is to press enter and move on. 
		state = SELECTION_SCREEN; //The screen now becomes the selection screen. 
	}
}
void Game::updateSelectionScreen(float ms) //The update function of the Selection Screen 
{
	graphics::MouseState mouse; //In this case it is important for the user to be able to use their mouse to select a character. 
	graphics::getMouseState(mouse);
	if (mouse.button_left_pressed) { //Depending on which position the user clicks on (the locations are ties to the locations of the character portraits)...
		if (mouse.cur_pos_y<=830 && mouse.cur_pos_y>=370) { //...the character on that position will be chosen. 
			if (std::abs(mouse.cur_pos_x-600)<=160) {
				chara = 0;
				enemy_init = false; //Also this is where the variables that will define if the boxes and enemies exist are set to false, so that they can be spawned since they do not exist yet... 
				box_init = false; //...whether that is if the game is being played for the first time or if it is restarted.
				game_over = false; //If the game has been lost in a previous playthrough, then game_over will be true, so it's important to update that. 
				state = GAME_SCREEN; //After the selection, the game moves on to the Game Screen. 
				
			}
			else if (std::abs(mouse.cur_pos_x - 940) <= 160){
				chara = 1;
				enemy_init = false;
				game_over = false;
				box_init = false;
				state = GAME_SCREEN;
			}
			else if (std::abs(mouse.cur_pos_x - 1370) <= 160) {
				chara = 2;
				enemy_init = false;
				game_over = false;
				box_init = false;
				state = GAME_SCREEN;
			}
		}

	}
}
void Game::updateGameScreen(float ms) //The update function of the Game Screen 
{
	if (this->player == nullptr) { //If the player does not exist, it is spawned and the appropriate character from the Selection Screen is also given.
		this->player = new Player(*this, chara);
	}
	if (this->player) {
		this->player->update(ms);
		this->player->setBeam(true); 
		if (!this->Shelter.empty()) {//If the boxes do not exist (which they shouldn't at this point) they are spawned.
			for (int i = 0; i < boxes; i++) {
				if (this->Shelter[i]->getHp() > 0.0f) {
					if (std::abs(this->player->getPosx() - Shelter[i]->getX()) < Shelter[i]->getSize() / 2) {
						this->player->setBeam(); //If the player is standing under a box, then its projectiles will not pass through.
					}
				}
			}
		}
	}

	if (!enemy_init) { //As the enemy_init is set to false each time a character is selected, now it is time to spawn enemies.
		spawnShredder(7,4);
		enemy_init = true;
	}

	if (!box_init) {//Similarly with the boxes. 
		this->spawnBoxes(4);
		box_init = true;
	}

	for (int i = 0; i < Shelter.size(); i++) { //When the boxes still exist, their update function should be called. 
		if (this->Shelter[i]->getHp() > 0.0f) {
			this->Shelter[i]->update(ms);
		}
	}

	CheckCollision(); //A call to the Collision function to check all the possible collisions between objects that can be collided.

	for (int i = 0; i < active_enemies; i++) {
		if (this->enemies[i]) {
			if (this->enemies[i]->isActive()) {//If any enemy exists and is active, their update function should be called. 
				this->enemies[i]->update(ms);
			}
		}
	}

	if (this->player->getHp() == 0.0f|| game_over) { //If the HP of the player runs out or the game_over variable is true, the game ends.
		delete this->player; //The player is deleted.
		this->player = nullptr;
		state = LOSS_SCREEN; //And the screen changes to the Loss Screen. 
		victory_offset = graphics::getGlobalTime() + 1000;
	}

	if (enemies_remaining == 0 && enemy_init) { //If there are no visible remaining enemies and enemy_init is true, the game ends.
		delete this->player; //The player is deleted.
		this->player = nullptr;
		state = VICTORY_SCREEN; //This time, it is a victory for the player so the screen changes to the Victory Screen. 
		victory_offset = graphics::getGlobalTime() + 1000;
	}
}
void Game::updateVictoryScreen(float ms) //The update function of the Victory Screen 
{
	if (graphics::getGlobalTime() > victory_offset) {
		victory_offset = 0.0f;
		if (graphics::getKeyState(graphics::SCANCODE_ESCAPE)) {
			if (enemies.size() != 0) {
				for (int i = enemies.size() - 1; i >= 0; i--) {
					delete enemies[i];
					enemies[i] == nullptr;
				}
				enemies.clear();
			}
			if (Shelter.size() != 0) {
				for (int i = Shelter.size() - 1; i >= 0; i--) {
					delete Shelter[i];
					Shelter[i] == nullptr;
				}
				Shelter.clear();
			}
			exit(0);
		}
		if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
			score = 0;
			if (enemies.size() != 0) {
				for (int i = enemies.size() - 1; i >= 0; i--) {
					delete enemies[i];
					enemies[i] == nullptr;
				}
				enemies.clear();
			}
			if (Shelter.size() != 0) {
				for (int i = Shelter.size() - 1; i >= 0; i--) {
					delete Shelter[i];
					Shelter[i] == nullptr;
				}
				Shelter.clear();
			}
			state = MENU_SCREEN;
		}
	}
}
void Game::updateLossScreen(float ms) //The update function of the Loss Screen. 
{
	if (graphics::getGlobalTime() > victory_offset) {
		victory_offset = 0.0f;
		if (graphics::getKeyState(graphics::SCANCODE_ESCAPE)) {
			if (enemies.size() != 0) {
				for (int i = enemies.size() - 1; i >= 0; i--) {
					delete enemies[i];
					enemies[i] == nullptr;
				}
				enemies.clear();
			}
			if (Shelter.size() != 0) {
				for (int i = Shelter.size() - 1; i >= 0; i--) {
					delete Shelter[i];
					Shelter[i] == nullptr;
				}
				Shelter.clear();
			}
			exit(0);
		}
		if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
			if (enemies.size() != 0) {
				for (int i = enemies.size() - 1; i >= 0; i--) {
					delete enemies[i];
					enemies[i] == nullptr;
				}
				enemies.clear();
			}
			if (Shelter.size() != 0) {
				for (int i = Shelter.size() - 1; i >= 0; i--) {
					delete Shelter[i];
					Shelter[i] == nullptr;
				}
				Shelter.clear();
			}
			score = 0;
			state = MENU_SCREEN;
		}
	}
}

void Game::draw()//The general draw function of the game. 
{ 
	//Background below the player
	graphics::Brush bruh_sh;
	bruh_sh.texture = this->Map;
	graphics::drawRect(600, 400, 1550, 1000, bruh_sh);
	if (state == MENU_SCREEN) {
		drawMenuScreen();
	}
	else if (state==SELECTION_SCREEN) {
		drawSelectionScreen();
	}
	else if (state == GAME_SCREEN) {
		drawGameScreen();
	}
	else if (state == VICTORY_SCREEN) {
		drawVictoryScreen();
	}
	else if (state == LOSS_SCREEN) {
		drawLossScreen();
	}
	
}

void Game::update(float ms) //The general update function of the game. 
{
	if (state == MENU_SCREEN) {
		updateMenuScreen(ms);
	}
	else if (state == SELECTION_SCREEN) {
		updateSelectionScreen(ms);
	}
	else if (state == GAME_SCREEN) {
		updateGameScreen(ms);
	}
	else if (state == VICTORY_SCREEN) {
		updateVictoryScreen(ms);
	}
	else if (state == LOSS_SCREEN) {
		updateLossScreen(ms);
	}

}

void Game::init()//Things that included in the game 
{
	graphics::setFont(std::string(ASSET_PATH) + "ARCADECLASSIC.ttf"); 
	int chara = 0;
}

Game::Game() { //Constructor

}

Game::~Game() //Destuctor 
{

}

void Game::CheckCollision() //The function that checks all of the possible collision outcomes. 
{
	if (this->player->getBullet()) { //If the player has thrown a bullet...
		if (this->player->getCharacter() == 2 || this->player->getCharacter() == 0) {//and is either character 0 or 2 (who have similar bullets)
			Disk d1 = this->player->getBullet()->getCollision(); //Then one disk of collision is created for its bullet 
			Disk d2;
			for (int i = 0; i < active_enemies; i++) { //This might affect any enemy on the board.
				if (this->enemies[i]->isActive()) {//...as long as the enemy is active...
					d2 = this->enemies[i]->getCollision();// The second disk becomes the enemy's collision. 
					float dx = (d2.getX() - d1.getX()); //Dx is the distance between the locations of the two disks on the x axis. 
					float dy = (d2.getY() - d1.getY()); //Dy is the distance between the locations of the two disks on the y axis. 
					if (sqrt(dy * dy + dx * dx) < d1.getR() + d2.getR()) { //If the distance between them is smaller than the radius of their collision circles...
						this->enemies[i]->Collide(this->player->getBullet());// ...then the bullet of the player and the enemy collide. 
						this->player->getBullet()->setActive(); //The bullet of the player disappears. 
						if (this->enemies[i]->getHp() == 0.0f) {//The enemy loses HP already through collision, but if it dies...
							score += 50; //...the score increases by 50...
							enemies_remaining--;//...and there is one less enemy left on the board. 
						}

					}
				}
			}
			for (int i = 0; i < boxes; i++) {// For all the boxes that are active. 
				if (this->Shelter[i]->getHp() > 0.0f) { //If their HP is more than 0 
					if (std::abs(d1.getX() - this->Shelter[i]->getX()) < this->Shelter[i]->getSize() / 2 && d1.getY() - d1.getR() <= this->Shelter[i]->getY() + (this->Shelter[i]->getSize() / 2)) {
						//If the player's location on the x axis is anywhere around the location of the box, then the player cannot throw bullets under it.
						this->player->getBullet()->setActive();
						graphics::playSound(std::string(ASSET_PATH) + "box.mp3", 0.4f, false);
					}
				}
			}

		}
		else {//If the character is 1, who has a different type of projectile.
			float d1 = this->player->getBullet()->getX(); //The location of the beam projectile on the x axis. 
			Disk d2;
			for (int i = active_enemies - 1; i >= 0; i--) {
				if (this->enemies[i]->isActive()) {
					d2 = this->enemies[i]->getCollision(); //Again, if an enemy is active, the second disk is its collision
					float dd = std::abs(d2.getX() - d1);// The distance between the beam's location and the enemy's collision
					if (dd < d2.getR() && this->player->getBullet()->getHit() < 2) { 
						this->enemies[i]->Collide(this->player->getBullet());
						if (this->enemies[i]->getHp() == 0.0f) {//If the enemy dies then the score increases and the active enemies become one less.
							score += 50;
							enemies_remaining--;
						}
					}

				}
			}
		}
	}
	for (int i = 0; i < active_enemies; i++) {
		if (this->enemies[i]->isActive()) {
			if (this->enemies[i]->getY() > BOX_BOTTOM - 225) game_over = true; //If the player fails to exterminate all the enemies before they reach the height of the boxes, they lose.
		}
		if (this->enemies[i]->getBullet()) {
			Disk d1 = this->enemies[i]->getBullet()->getCollision();
			Disk d2;
			if (this->player) {
				d2 = this->player->getCollision();
				float dx = (d2.getX() - d1.getX());
				float dy = (d2.getY() - d1.getY());
				if (sqrt(dy * dy + dx * dx) < d1.getR() + d2.getR()) {
					this->player->Collide(this->enemies[i]->getBullet());
					this->enemies[i]->getBullet()->setActive();

				}
			}
			for (int j = 0; j < boxes; j++) {
				if (this->Shelter[j]->getHp() > 0.0f) {
					if (d1.getY() + d1.getR() > Shelter[j]->getY() - (Shelter[j]->getSize() / 2) && std::abs(d1.getX() - Shelter[j]->getX()) < Shelter[j]->getSize() / 2) {
						this->Shelter[j]->Collide(this->enemies[i]->getBullet());
						this->enemies[i]->getBullet()->setActive();
					}
				}
			}

		}
	}
}
