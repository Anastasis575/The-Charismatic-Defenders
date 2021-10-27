#pragma once
#include "ObjInterface.h"
#include "Disk.h"
#include "Projectile.h"
#include "General.h"
#include "graphics.h"
#include "scancodes.h"
#include "Collidable.h"
#include "CollisionSusceptible.h"

//The playable character that the user can play as and represents the user's input on the game. 

class Player : public ObjInterface, public Collidable, public CollisionSusceptible{ //It inherits both the ability to collide and be collidable
	float posx = 0.0f; //The player's position on the x axis.
	const float posy= BOX_BOTTOM-30; //The player's y position cannot be changed. 
	float speed = 2.0f; //How fast the player can move.
	float hp = 3.0f;// The player's HP.
	int character = 0; //The character of the player (the default state is 0)
	float end_interval=0.0f; //A small interval for the player to be able to shoot the beam projectile. 
	bool beamin = true; //If the player can shoot bullets (cannot if it is behind a box). 
	Projectile* bullets=nullptr;//The player has one bullet at a time. 
public:
	Player(const class Game& myGame, int character); //Constructor.
	virtual void update(float ms) override;
	virtual void draw() override;
	virtual void init() override;
	int getCharacter() { return character; } //Returns the current character of the player. 
	float getHp() { return hp; } //Returns the  HP of the player. 
	bool getBeam()const { return this->beamin; }; //Returns whether the projectile exists or not.
	void setBeam(bool beam = false) { this->beamin = beam; };//Changes the state of the projectile.
	virtual Disk getCollision() override; //The player can be collided with. 
	Projectile* getBullet(); //And it can also have  a bullet, which this function returns. 
	float getPosx() const; //Returns the position of the player
	virtual void Collide(Projectile* bu) override; //The projectiles of the player can collide. 
};
