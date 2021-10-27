#pragma once
#include "graphics.h"
#include "scancodes.h"

class Disk { //A simple disk class that will define the parameters of the collision disks used in the game. 
public:
	float posx, posy, rad = 0;
	Disk(); // Default Constructor
	~Disk(); //Destructor
	Disk(float x, float y, float radi); //Constructor
	void drawCollisionDisk(); //The disk also has a draw function, for debug purposes.
	float getX() { return posx; } //Returns the x position of the disk
	float getY() { return posy; } //Returns the y position of the disk
	float getR() { return rad; } //Returns the x position of the disk
};