#include "General.h"
#include "Game.h"
#include "graphics.h"
#include "scancodes.h"

//The general class for all things that are tied to the program itself.

void update(float ms) {
	Game* za_gaemu = reinterpret_cast<Game*>(graphics::getUserData());
	za_gaemu->update(ms);
}
void draw() {
	Game* za_gaemu = reinterpret_cast<Game*>(graphics::getUserData());
	za_gaemu->draw();
	
}
	
int main() {
	graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT,"The Charismatic Defenders");//We create a window with the desired measurements .
	Game* za_gaemu=new Game();//The game instance.
	graphics::setUserData(za_gaemu);//We declare the game instance known in all Callbacks of our game.
	graphics::setUpdateFunction(update);//We set an update function callback.
	graphics::setDrawFunction(draw);//and a draw function Callback.
	graphics::playMusic("assets\\Vitality.mp3", 0.5f, true);//The soundtrack of the game.

	graphics::setCanvasSize(1200, 800);//We create a Canvas to upload everything drawable
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);//And how the canvas fits the screen 
	graphics::setFullScreen(true);//We set fullscreen

	
	graphics::Brush brr;
	graphics::setWindowBackground(brr);//And the default background is a white box
	
	graphics::startMessageLoop();
}