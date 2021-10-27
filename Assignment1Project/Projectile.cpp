#include "Projectile.h"
#include "General.h"

//The player and enemies can throw projectiles at each other, this is the class that gives them properties and defines them. 

Projectile::Projectile(int state, bool tomodachi, float posx, float posy, float speed) : posx(posx), posy(posy), speed(speed), state(state) , friendly(tomodachi){
	if (this->state == 1) { //When the state of the projectile is 1, it means it's the beam projectile, which works a bit differently.
		binterval = graphics::getGlobalTime() + 1000; //Its interval before being shot again is one second.
		opacity = 1.0f; //It starts with a full opacity.
		beam_hit = 0; //And hasn't hit any enemy so far. 
	}

}

void Projectile::update(float ms) //The update function of the projectile
{
	if (this->getState() == 0 || this->getState()==2) { //When the state is 0 or 2 (representing characters 0 and 2)
		this->posy -= (speed * graphics::getDeltaTime()) / 5; //The projectile keeps going up. 
		if (posy < BOX_TOP ) { this->active = false; } //If it hits the top of the playing box, it disappears. 
	}
	else if( this->getState()==1){//When the state is 1, which is the beam projectile of character 1 
		if (binterval < graphics::getGlobalTime()) { //When the interval has passed, the projectile is set to active. 
			this->setActive();
		}
	}
	else if (this->getState()==3){//When the state is 3, it's an enemy projectile. 
		this->posy += (speed * graphics::getDeltaTime()) / 5; //The projectile keeps going down.
		if (posy > BOX_BOTTOM) { this->active = false; } //If it hits the bottom of the playing box, it disappears. 
	}

}

void Projectile::draw() //The draw function of the projectile
{
	graphics::Brush brush;
	if (this->getState() == 3) { //Drawing the projectile of the enemy.
		graphics::setOrientation(180);//It is facing downwards. 
		brush.outline_opacity = 0.0f;
		brush.texture = std::string(ASSET_PATH) + "PROJECTILE3.png";
		graphics::drawRect(posx, posy, 16, 43, brush);
	}
	else if (this->getState() ==2) {//Character 2's projectile.
		graphics::setOrientation(90);
		brush.outline_opacity = 0.0f;
		brush.texture = std::string(ASSET_PATH) + "SHOT.png";
		graphics::drawRect(posx, posy, 25, 6, brush);
	}
	else if (this->getState()==1 && graphics::getGlobalTime()<=binterval){//Character 1's projectile. 
		graphics::setOrientation(0);
		brush.outline_opacity = 0.0f;
		brush.texture = std::string(ASSET_PATH) + "BLAST.png";
		brush.fill_opacity = opacity;
		opacity -= graphics::getDeltaTime()/150; //Its opacity gradually becomes smaller as time passes, so it fades out. 
		graphics::drawRect(posx, posy-345, 51, 631, brush);

	}
	else if (this->getState() == 0) { //Character 0's projectile. 
		graphics::setOrientation(0);
		brush.outline_opacity = 0.0f;
		brush.texture = std::string(ASSET_PATH) + "PROJECTILE2.png";
		graphics::drawRect(posx, posy, 16,43, brush);
	}
	graphics::resetPose(); //Restores the orientation of the projectile. 
}

Projectile::~Projectile() //Constructor
{
}

Disk Projectile::getCollision() 
{
	return Disk(posx,posy,15); //Creates a collision disk for the projectile. 
}

float Projectile::getY() const //Returns the y of the projectile.
{
	return posy;
}

float Projectile::getX() const //Returns the x of the projectile.
{
	return posx;
}

int Projectile::getState() const //Returns the state of the projectile.
{
	return state;
}

bool Projectile::getFriendly() const //Returns true if the projectile is friendly.
{
	return friendly;
}

int Projectile::getHit() const //Returns the number of hits of the beam.
{
	return beam_hit;
}

bool Projectile::getActive() const //Returns true if the projectile is active.
{
	return active;
}

float Projectile::getDamage() const //Returns the damage of the projectile.
{
	if (state == 0) {
		return 4.0f;
	}
	else if (state == 1|| state==3) {
		return 1.0f;
	}
	else if (state == 2) {
		return 2.0f; 
	}
	return 0.0f;
}

float Projectile::getBinterval() //Returns the interval of the beam projectile.
{
	return binterval;
}
