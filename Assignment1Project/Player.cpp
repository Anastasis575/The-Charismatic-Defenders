#include "General.h"
#include "Game.h"
#include "graphics.h"
#include "scancodes.h"
#include "Player.h"
#include "ObjInterface.h"

//The playable character that the user can play as and represents the user's input on the game. 

Player::Player(const Game& mygame, int character): ObjInterface(mygame), character(character) //Constructor 
{
}

void Player::update(float ms) //The update function of the player
{
	if (this->hp!= 0) { //If the player doesn't have 0 HP (meaning it is alive) 
		if (graphics::getKeyState(graphics::SCANCODE_RIGHT)) { //The player moves right when the right button is pressed. 
			this->posx += speed * graphics::getDeltaTime() / 10.0f;
		}

		if (graphics::getKeyState(graphics::SCANCODE_LEFT)) { //The player moves left when the left button is pressed.
			this->posx -= speed * graphics::getDeltaTime() / 10.0f;
		}
		if (this->beamin) { //If the player is an a position where it can shoot bullets...
			if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {//...and if space is pressed...
				if (!this->bullets) {//...without a bullet already existing. 
					if (this->character == 0) { //Depending on the character, a different projectile is shot, with different speed and sound effect. 
						this->bullets = new Projectile(0, true, this->posx + 5, this->posy, 1.0f);
						graphics::playSound(std::string(ASSET_PATH) + "ChordBlast.wav", 0.1f, false);
					}
					else if (this->character == 1) {
						if (graphics::getGlobalTime() > end_interval) { //With character 1 it is important that the interval has passed before it can shoot again. 
							this->bullets = new Projectile(1, true, this->posx + 5, this->posy, 0.0f);
							graphics::playSound(std::string(ASSET_PATH) + "EldBlast.mp3", 0.2f, false);
							end_interval = graphics::getGlobalTime() + 1000;
						}
					}
					else if (this->character == 2) {
						this->bullets = new Projectile(2, true, this->posx + 5, this->posy, 3.0f);
						graphics::playSound(std::string(ASSET_PATH) + "pew.mp3", 0.5f, false);
					}
				}
			}
		}
		if (this->bullets) {//If the bullet exists...
			if (!this->bullets->getActive()) { //...but is not activated...
				delete this->bullets;//...then it is deleted. 
				this->bullets = nullptr; 
			}
			else {
				this->bullets->update(ms); //Otherwise it is updated. 
			}
		}
		if (posx < 633 - CANVAS_WIDTH / 2) posx = 633 - CANVAS_WIDTH / 2; //The player cannot get out of the playing box. 
		if (posx > 567 + CANVAS_WIDTH / 2) posx = 567 + CANVAS_WIDTH / 2;
	}
}

void Player::draw()// The draw function of the player. 
{
#ifdef _Debug
	Disk dousk = this->getCollision();
	dousk.drawCollisionDisk();
#endif // _Debug
	graphics::setOrientation(0);
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	if (this->character == 0) { //Again, depending on the character, a different image is drawn. 
		br.texture = std::string(ASSET_PATH) + "Konton.png";
	}
	else if (this->character == 1) {
		br.texture = std::string(ASSET_PATH) + "Yuvo.png";
	}
	else if (this->character == 2) {
		br.texture = std::string(ASSET_PATH) + "Klaus.png";
	}
	graphics::drawRect(posx, this->posy, 55, 55, br);

	if (this->bullets && this->bullets->getActive()) { //If the bullet exists and it is active then it too is drawn. 
		this->bullets->draw();
	}

}

void Player::init() //Everything inside the player. 
{
	this->end_interval = graphics::getGlobalTime();
}


Disk Player::getCollision() //The player can be collided with.
{
	return Disk(posx, this->posy, 25); //The Collision disk of the player. 
}

Projectile* Player::getBullet() //Returns the bullet 
{
	return this->bullets;
}

float Player::getPosx() const //Returns the position of the player
{
	return this->posx;
}

void Player::Collide(Projectile* bu) //The projectiles of the player can collide. 
{
	this->hp -= (*bu).getDamage(); //Whenever a collision happens, the player loses HP corresponding to the damage of the projectile. 
	graphics::playSound(std::string(ASSET_PATH) + "hurt.mp3", -0.6f, false);
}
