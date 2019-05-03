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

	MainProgram() 
	{
		windowW = 1000, windowH = 500;
	}

	void init();

	void drawString(void *font, float x, float y, const char *str);

	std::string IntToStr(int n);

	void status();

	void collisions();

	float windowW;
	float windowH;
	float gametime = 0;

	Ground *ground = NULL;
	Image *background = NULL;
	Lander *lander = NULL;// (startx, starty, startradius);

private:

	float aspect; 
	bool clearScreen;

	float startx;// = rand() % 900 + 100;
	float starty;// = rnd(350, 450);
	int startradius;// = 10;


	std::string *t;// (" ");
	std::string *fuel;// (" ");
	std::string *altitude;// (" ");
};