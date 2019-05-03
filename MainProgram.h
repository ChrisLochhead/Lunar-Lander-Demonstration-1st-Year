#pragma once
#include<iostream>
#include<ctime>
#include"random.h"
#include"lander.h"
#include"ground.h"
#include<sstream>	
#include<stdexcept>		
#include<string>
#include "Image.h"

class MainProgram {
public:

	MainProgram() {}

	void init();

	void drawString(void *font, float x, float y, const char *str);

	std::string IntToStr(int n);

	void status();

	void collisions();

	Lander* getLander() { return lander; }
	Ground* getGround() { return ground; }
	Image* getBackground() { return background; }

	float windowW;
	float windowH;
	float gametime = 0;

private:

	float aspect; 
	bool clearScreen;

	float startx;// = rand() % 900 + 100;
	float starty;// = rnd(350, 450);
	int startradius;// = 10;

	Ground *ground = NULL;
	Image *background = NULL;

	Lander *lander;// (startx, starty, startradius);

	std::string *t;// (" ");
	std::string *fuel;// (" ");
	std::string *altitude;// (" ");
};