#pragma once
#include "Disk.h"
#include "Collidable.h"

//The player and enemies can throw projectiles at each other, this is the class that gives them properties and defines them. 

class Projectile: public Collidable {
	int state=0; //4 states of projectiles, 0-2 for the players, 3 for the enemies. 
	float posx = 0.0f;//Position of the projectile on the x axis. 
	float posy=0.0f; //Position of the projectile on the x axis. 
	bool friendly;//Whether the projectile is friendly or not.
	int beam_hit = 0; //For state 1, checking how many enemies the beam projectile hits.
	float binterval = 0; //Inteval for the beam before the player can shoot again. 
	float opacity = 0.0f;//The opacity of the beam, that decreases progressively after it is fired. 
	float speed = 5.0f;//The speed of the projectile. 
	bool active=true;//Whether the projectile exists or not. 
public:
	Projectile(int state,bool tomodachi, float posx, float posy, float speed); //Constructor
	void update(float ms);
	void draw();
	~Projectile();
	virtual Disk getCollision() override; //The collision of the projectiles
	float getY() const;//Returns the y of the projectile.
	float getX() const; //Returns the x of the projectile.
	int getState() const; //Returns the state of the projectile.
	bool getFriendly() const; //Returns true if the projectile is friendly.
	int getHit() const; //Returns the number of hits of the beam. 
	void incrBeamHit() { this->beam_hit += 1; } //Increases the number of hits of the beam. 
	bool getActive() const;//Returns true if the projectile is active.
	float getDamage() const;//Returns the damage of the projectile.
	float getBinterval(); //Returns the interval of the beam projectile.
	void setHitTrue() { this->beam_hit = true; }
	void setActive() { this->active = !this->active; }
};