#include "Boxes.h"
#include "Game.h"
#include "graphics.h"

Box::Box(const Game& myGame, float posx, float posy) : ObjInterface(myGame),posx(posx), posy(posy) //Constructor
{
	this->init();
}

Box::~Box() //Destructor
{
}

void Box::init() //All things inside the boxes.
{
	this->hp = 40.0f;
	this->size = 90;
}

void Box::update(float ms) //The update function of the box 
{
}

void Box::draw()//Draws all versions of the box, regarding the HP.
{
	if (hp > 0.0f) {
		graphics::Brush BoxBrush;
		BoxBrush.outline_opacity = 0.0f;
		if (hp > 30.0f) {
			BoxBrush.texture =std::string(ASSET_PATH)+ "bonker.png";//If the box has 100%-75% the box looks healthy.
		}
		else if (hp > 20.0f) {
			BoxBrush.texture = std::string(ASSET_PATH) + "bonker2.png";//If the box has 75%-50% the box shows slight damage.
		}
		else if (hp > 10.0f) {
			BoxBrush.texture = std::string(ASSET_PATH) + "bonker3.png";//If the box has less than 25%- 50%, it shows signs of severe damage. 
		}
		else {
			BoxBrush.texture = std::string(ASSET_PATH) + "bonker4.png";//Lastly, if the the box has less than 25%, it is in the brink of destruction.
		}
		graphics::drawRect(posx, posy, size, size, BoxBrush);
	}
}

float Box::getHp() const //Returns the HP of the box. 
{
	return this->hp;
}

float Box::getY() const // Returns y of the box
{
	return this->posy;
}

float Box::getX() const // Returns x of the box
{
	return this->posx;
}
void Box::Collide(Projectile *bu) {//When the box collides with a bullet its HP decreases.
	this->hp -= bu->getDamage();
	graphics::playSound(std::string(ASSET_PATH) + "box.mp3", 0.4f, false);
}