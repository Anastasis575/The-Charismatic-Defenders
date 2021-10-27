#pragma once


class ObjInterface {//This is the class that forces each object that is generated in the game to have the essential 
protected:
	const class Game& game;
public:
	ObjInterface(const class Game& mygame);
	virtual void update(float ms) = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
};
