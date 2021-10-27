#include "Enemy.h"
#include "graphics.h"
#include <random>
#include "Game.h"
#include "ObjInterface.h"


//As it is natural, every game includes enemies. The enemies can shoot projectiles or collide with the boxes if they move too far down.

void Enemy::update(float ms){ //The update function for the enemy 
	if (graphics::getGlobalTime() >= interval ) { //When a certain interval has passed.
	
		if (this->stepcounter != max_steps) { //If the max step has not been reached... 
			posx+=20*orientation;//then the enemy moves on the x axis. 
			}
		if (this->stepcounter == max_steps) { //If it has been reached...
			this->stepcounter = 0; //...the stepcounter starts again.
			orientation *= -1; //The orientation changes, so now the enemy moves on the opposite direction.
			posy += speed; 
			step++;
		}
		if (std::div(step, 2).rem == 0) { //If step%2=0
			this->time_offset = 1000 - std::div(step, 2).quot * 200;  //As the enemies keep moving downward, they speed up.
			if (this->time_offset <= 300)this->time_offset = 300;
		}
		this->stepcounter += 1;
		interval = graphics::getGlobalTime()+time_offset;
	}
	if (hp==0.0f) { //If the enemy has 0 HP it is not active anymore. 
		active = false;
	}
	if (posy > 567 + CANVAS_HEIGHT / 2) posy = 567 + CANVAS_HEIGHT / 2; //The enemy can only go so down on the playing box.

	if (graphics::getGlobalTime() > beam_interval) { //The certain interval that passes before an enemy can shoot another bullet
		this->enemy_bullets = new Projectile(3, false, this->posx - 5, this->posy+10, 2.0f);
		beam_interval=graphics::getGlobalTime()+ (rand() % ((20 - 8) + 1) + 2) * 1000; 
		/*Let it be noted that with the amount of enemies on the board, a lot of bullets can come out at the same time, but each
		enemy has to wait for a random interval before shooting again*/
	}
	if (this->enemy_bullets) {//If an enemy bullet has been created...
		if (!this->enemy_bullets->getActive()) {//...but isn't active anymore...
			delete this->enemy_bullets;//...it is deleted.
			this->enemy_bullets = nullptr;
		}
		else {//Otherwise its state is updated.
			this->enemy_bullets->update(ms);
		}
	}
}

void Enemy::draw()//The draw function of the enemy 
{
#ifdef _Debug
	Disk dousk = this->getCollision();
	dousk.drawCollisionDisk();
#endif // _Debug

	graphics::Brush brush;
	graphics::setOrientation(0);
	brush.texture = std::string(ASSET_PATH) + "ENEME.png";
	brush.fill_opacity = 1.0f;
	brush.outline_opacity = 0.0f;
	graphics::drawRect(posx, posy, size, size, brush);
	graphics::resetPose();
	if (this->enemy_bullets && this->enemy_bullets->getActive()) {
		this->enemy_bullets->draw(); //The bullets are drawn as well if they are active.
	}
}

void Enemy::init() //Everything included in the enemy 
{
	speed = 20.0f;
	time_offset = 1000;
	interval = graphics::getGlobalTime()+2000;
	size = 40; 
	orientation = 1; 
	beam_interval = graphics::getGlobalTime() + (rand() % ((20 - 8) + 1) + 2)*1000;
	max_steps = 7;
}

Disk Enemy::getCollision()//The enemy has a collision too, although smaller than the player's, making it more challenging to hit.
{
	return Disk(posx,posy,10);
}

Projectile* Enemy::getBullet() //Returns the bullet.
{
	return this->enemy_bullets;
}

Enemy::Enemy(const Game& mygame,float posx,float posy) : ObjInterface(mygame), posx(posx),posy(posy) //Constructor
{
	init();
}

Enemy::~Enemy() //Destructor
{
}

void Enemy::Collide(Projectile *bu) //The enemy can be collided with by player bullets.
{
	this->hp -= (*bu).getDamage();
	if ((*bu).getState() == 1) (*bu).incrBeamHit(); //And whenever they are hit by character 1's beam, the amount of enemies the beam has hit increases.
	if (this->hp == 0.0f) { //The enemy has different sounds for getting hit and dying 
		graphics::playSound(std::string(ASSET_PATH) + "Enemy_death.mp3", 0.4f, false);
	}
	else {
		graphics::playSound(std::string(ASSET_PATH) + "enemy_hurt.mp3", 0.4f, false);
	}
}
