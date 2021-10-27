#pragma once
#include "ObjInterface.h"
#include "graphics.h"
#include "Projectile.h"
#include "General.h"
#include "Disk.h"
#include "Collidable.h"
#include "CollisionSusceptible.h"

//As it is natural, every game includes enemies. The enemies can shoot projectiles or collide with the boxes if they move too far down. 

class Enemy : public ObjInterface, public Collidable, public CollisionSusceptible {
	float posx, posy;//The positioning of the enemy. 
	float speed; //The speed of the enemy. 
	float size; //The size of the enemy. 
	float time_offset = 0.0f;
	float hp = 4.0f; //The HP of the enemy. 
	int stepcounter = 0; //The steps the enemy takes before changing direction.
	int orientation = 1; //The enemy's orientation
	int step = 0; //How many steps down the enemy has taken. 
	bool active = true; //Whether the enemy is active. 
	Projectile* enemy_bullets = nullptr; //The enemy has a projectile.
	float interval = 0.0f; //Interval before moving again. 
	int max_steps = 0; //The maximum amount of steps an enemy can take.
	float beam_interval = 0.0f; //Interval between projectiles thrown among enemies. 

public:
	void update(float ms) override;
	void draw() override;
	void init() override;
	bool isActive() { return active; } //Whether the enemy is active or not.
	float getHp() const { return this->hp; }; //Returns the enemy's HP.
	float getY() const { return posy; }; //Returns the y of the enemy.
	virtual Disk getCollision() override; //The enemy has a collision. 
	Projectile* getBullet();//And a bullet. 
	void setMaxStep(int step) { this->max_steps = step; }; //Sets a new max step for the enemies.
	int getMaxStep()const { return this->max_steps; }; //Returns the max step. 
	Enemy(const class Game& mygame,float posx,float posy= 50.0f);//Constructor
	~Enemy(); //Destructor
	virtual void Collide(Projectile* bu) override; //The enemy can be collided with the player's bullets.
};

