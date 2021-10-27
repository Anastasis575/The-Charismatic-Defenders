#pragma once
#include "General.h"
#include <string>
#include <math.h>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Boxes.h"
#include <cmath>

//General things about the game. 

class Game{

	typedef enum { MENU_SCREEN, SELECTION_SCREEN, GAME_SCREEN, VICTORY_SCREEN, LOSS_SCREEN} game_status; //All the possible game screens.
	std::string Map = "assets\\Map3.png"; //The background is always the same.
	//Generally, all the values related to the basics of the game, such as:
	int active_enemies = 0; //The number of active enemies.
	int enemies_remaining = 0; //The number of remaining enemies, for the win condition. 
	bool enemy_init = false; //Whether the enemies exist.
	bool box_init = false; //Whether the boxes exist.
	bool game_over = false; //Whether the game is still going on.
	float victory_offset = 0.0f;//A time offset to delay input in the victory and loss screen.
	int chara = 0; //The character chosen.
	int boxes = 0; //The number of boxes.
	int score = 0; //The score.
	Player* player= nullptr; //The creation of the player.
	game_status state = MENU_SCREEN; //The state of the game, or the "game screen". 
	std::vector<Box*> Shelter;//The creation of the boxes.
	std::vector<Enemy*> enemies; //The creation of the enemies. 
	void spawnBoxes(int box = 3);
	void spawnShredder(int number = 5, int lines=1);
	void drawMenuScreen(); //All the update and draw functions for the game screens. 
	void drawSelectionScreen();
	void drawGameScreen();
	void drawVictoryScreen();
	void drawLossScreen();
	void updateMenuScreen(float ms);
	void updateSelectionScreen(float ms);
	void updateGameScreen(float ms);
	void updateVictoryScreen(float ms);
	void updateLossScreen(float ms);

public:
	void draw(); //The overall draw function for the game.
	void update(float); //The overall update function for the game.
	void init(); //Anything that exists within the game.
	Game(); //Constructor
	~Game(); //Destructor
	void CheckCollision(); //The general collision function for objects that will potentially collide with each other during the game. 
};


