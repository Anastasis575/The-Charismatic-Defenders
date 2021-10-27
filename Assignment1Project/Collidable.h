#pragma once
#include "Disk.h"
class Collidable {//Shows that the object has collision disk.
public:
	Collidable() {};
	virtual Disk getCollision() = 0;
};