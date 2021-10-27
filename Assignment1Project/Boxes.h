#pragma once
#include "graphics.h"
#include "scancodes.h"
#include <string>
#include "General.h"
#include "ObjInterface.h"
#include "Projectile.h"
#include "CollisionSusceptible.h"


class Box : public ObjInterface, public CollisionSusceptible {
	float hp, posx, size = 0.0f;//Box's HP, x position and size
	const float posy;//and its y position.
public:
	Box(const Game& myGame, float posx, float posy); //Constructor
	~Box(); //Destructor
	void init();
	void update(float ms);
	void draw();
	virtual void Collide(Projectile *bu) override; //The box can be collided with
	float getX() const; //Returns x of the box.
	float getY() const;//Returns y of the box.
	float getSize()const { return this->size; }; //Returns the size of the box, which cannot be modified. 
	float getHp() const; //Returns the HP of the box. 
};