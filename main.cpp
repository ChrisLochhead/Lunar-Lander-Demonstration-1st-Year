
#include<iostream>
#include"random.h"
#include"lander.h"
#include"ground.h"
#include<sstream>	
#include<stdexcept>		
#include<string>
#include "Image.h"
#include"Bitmap.h"

using namespace std;

float windowW = 1000, windowH = 500; float aspect; bool clearScreen;
float startx = rnd(100,900); float starty = rnd(350,450); int startradius = 10; 

Ground *theground = NULL;	
Image *background = NULL;

Lander lander(startx, starty, startradius);		

float gametime = 0;		
string thetime(" ");	
string thefuel(" ");	
string altitude(" ");	

void init()
{
	//initialise glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) { // glewInit failed, something is seriously wrong
		std::cout << "glewInit failed, aborting." << endl;
		exit(1);
	}

	theground = new Ground;
	background = new Image("background.bmp", glm::vec2(500.0f, 250.0f), 1000, 500);
}

void drawString(void *font, float x, float y, const char *str)		
{																	
	char *ch;														
	glRasterPos3f(x, y, 0.0);										
	for(ch=(char*)str; *ch ; ch++)									
		glutBitmapCharacter(font, (int)*ch);						
}																

std::string IntToStr(int n)		
{									
  std::ostringstream result;		
  result << n;						 
  return result.str();			
}									

void statusmsg()	
{
	if(lander.getDy() != 0) 
		gametime += 0.002f;

	thefuel = IntToStr(lander.getfuel());		
	thetime = IntToStr((int)gametime);			
	altitude = IntToStr((int)lander.gety());	

	glColor3f(1, 1, 0);
	drawString(GLUT_BITMAP_HELVETICA_12, 20, 20, "fuel: ");
	drawString(GLUT_BITMAP_HELVETICA_12, 50, 20, thefuel.c_str());		

	drawString(GLUT_BITMAP_HELVETICA_12, 100, 20, "Time: ");			
	drawString(GLUT_BITMAP_HELVETICA_12, 130, 20, thetime.c_str());		

	drawString(GLUT_BITMAP_HELVETICA_12, 180, 20, "Altitude: ");		
	drawString(GLUT_BITMAP_HELVETICA_12, 230, 20, altitude.c_str());	

	if(lander.gety() > 1000)	
		{
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, 100, 350, "your out the game! Press R to try do it properly");
			lander.stop();
		}
	if(lander.getfuel() < 1)	
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, 100, 250, "You're outta diesel bud!");
}


void collisions()
{
	if(lander.gety() - lander.heightLeftAboveGround(theground) == lander.gety() - lander.heightRightAboveGround(theground))  // if both legs are on a landing platform
		{
			if(((lander.gety() - lander.heightLeftAboveGround(theground)) < 16) && lander.gety() - lander.heightRightAboveGround(theground) < 16)	 //if at ground level
				{
					lander.stop();
					drawString(GLUT_BITMAP_TIMES_ROMAN_24, 100, 250, "skitz mate nice one! Press R to play again");
				}	
		}
	else	
		{
			if(((lander.gety() - lander.heightLeftAboveGround(theground)) < 16) && lander.gety() - lander.heightRightAboveGround(theground) < 16)	//if at ground level
				{
					lander.stop();
					drawString(GLUT_BITMAP_TIMES_ROMAN_24, 100, 220, "failure! Press R and try not suck this time");
				}
		}
}

void display(void)
{
	//clear the buffer
	glClear(GL_COLOR_BUFFER_BIT);
	//disable texturing from drawing text onto the screen
	glDisable(GL_TEXTURE_2D);

	background->draw();
	theground->show();
	lander.show();

	collisions();

	statusmsg();	

	glutSwapBuffers();
}


void keysdown(unsigned char key, int x, int y)		
{
	switch(key)
	{
		
		case 'w':				// UP
			if(lander.getfuel() > 0)
				lander.incrementVel(0, 0.05);
			else
				lander.incrementVel(0,0);
			break;
		case 'a':				// LEFT
			if (lander.getfuel() > 0)
				lander.incrementVel(-0.05, 0);
			else
				lander.incrementVel(0, 0);
			break;
		case 'd':				// RIGHT
			if (lander.getfuel() > 0)
				lander.incrementVel(0.05, 0);
			else
				lander.incrementVel(0, 0);
			break;
		case 'r':				// Reset 
			lander.reset();
			gametime = 0;
			break;
		case 27:				//  EXIT
			exit(0);
			break;
	}
}

void special_keys(int key, int x, int y)	// ARROW KEYS
{
	switch(key) 
	{
		case GLUT_KEY_UP:					// ARROW UP
			if(lander.getfuel() > 0)
				lander.incrementVel(0, 0.03);
			else
				lander.incrementVel(0,0);
			break;
		case GLUT_KEY_RIGHT:				// ARROW RIGHT
			if(lander.getfuel() > 0)
				lander.incrementVel(0.02, 0);
			else
				lander.incrementVel(0,0);
			break;
		case GLUT_KEY_LEFT:					// ARROW LEFT
			if(lander.getfuel() > 0)
				lander.incrementVel(-0.02, 0);
			else
				lander.incrementVel(0,0);
			break;
	}
}

void timer(int value)//update display, gravity and check for collision every 20 milliseconds
{
	display();

	lander.gravity();			
	lander.windowcollisions();	
	
	glutTimerFunc(20, timer, 0);
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize((int)windowW,(int)windowH);
	glutCreateWindow("Lunar Lander game");
	gluOrtho2D(0, windowW, 0, windowH);
	init();
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutDisplayFunc(display);
	glutTimerFunc(20, timer, 0);
	glutIdleFunc(display);
	glutKeyboardFunc(keysdown);
	glutSpecialFunc(special_keys);
	glutMainLoop(); 
}