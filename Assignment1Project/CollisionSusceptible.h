#pragma once
#include "Projectile.h"
class CollisionSusceptible {//Shows that the object can be collided with.
public:
	CollisionSusceptible() {};
	virtual void Collide(Projectile* bu) = 0;
};