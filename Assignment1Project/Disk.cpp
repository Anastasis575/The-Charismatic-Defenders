#include "Disk.h"

Disk::Disk() // Default Constructor
{
}

Disk::~Disk() //Destructor
{
}

Disk::Disk(float x, float y, float radi): posx(x), posy(y),rad(radi){ //Constructor
}

void Disk::drawCollisionDisk() //Draws the collision circle of the disk 
{
	graphics::Brush diskBrush;
	diskBrush.fill_color[0] = 0.99f;
	diskBrush.fill_color[1] = 0.89f;
	diskBrush.fill_color[2] = 0.01f;
	diskBrush.fill_opacity = 0.4f;
	diskBrush.outline_opacity = 0.0f;
	graphics::drawDisk(posx, posy, rad, diskBrush);
}


