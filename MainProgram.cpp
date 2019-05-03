#include "MainProgram.h"
#include "GL/glut.h"
using namespace std;

void MainProgram::init()
{
	//initialise glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) { // glewInit failed, something is seriously wrong
		std::cout << "glewInit failed, aborting." << endl;
		exit(1);
	}

	ground = new Ground;
	background = new Image("background.bmp", glm::vec2(500.0f, 250.0f), 1000, 500);

	//reseed the program at every compilation
	srand(time(0));
	windowW = 1000, windowH = 500;
	startx = rand() % 900 + 100; 
	starty = rand() % 450 + 350; 
	startradius = 10;

	lander = new Lander(startx, starty, startradius);

	 t = new std::string(" ");
	fuel = new std::string(" ");
	altitude = new std::string(" ");

}

void MainProgram::drawString(void *font, float x, float y, const char *str)		
{																	
	char *ch;														
	glRasterPos3f(x, y, 0.0);										
	for(ch=(char*)str; *ch ; ch++)									
		glutBitmapCharacter(font, (int)*ch);						
}																

std::string MainProgram::IntToStr(int n)		
{									
  std::ostringstream result;		
  result << n;						 
  return result.str();			
}									

void MainProgram::status()
{
	if(lander->getDy() != 0) 
		gametime += 0.002f;

	*fuel = IntToStr(lander->getfuel());		
	*t = IntToStr((int)gametime);			
	*altitude = IntToStr((int)lander->gety());	

	glColor3f(1, 1, 0);
	drawString(GLUT_BITMAP_HELVETICA_12, 20, 20, "fuel: ");
	drawString(GLUT_BITMAP_HELVETICA_12, 50, 20, fuel->c_str());		

	drawString(GLUT_BITMAP_HELVETICA_12, 100, 20, "Time: ");			
	drawString(GLUT_BITMAP_HELVETICA_12, 130, 20, t->c_str());		

	drawString(GLUT_BITMAP_HELVETICA_12, 180, 20, "Altitude: ");		
	drawString(GLUT_BITMAP_HELVETICA_12, 230, 20, altitude->c_str());	

	if(lander->gety() > 1000)	
		{
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, 100, 350, "your out the game! Press R to try do it properly");
			lander->stop();
		}
	if(lander->getfuel() < 1)	
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, 100, 250, "You're outta diesel bud!");
}


void MainProgram::collisions()
{
	if(lander->gety() - lander->heightLeftAboveGround(ground) == lander->gety() - lander->heightRightAboveGround(ground))  // if both legs are on a landing platform
		{
			if(((lander->gety() - lander->heightLeftAboveGround(ground)) < 16) && lander->gety() - lander->heightRightAboveGround(ground) < 16)	 //if at ground level
				{
					lander->stop();
					drawString(GLUT_BITMAP_TIMES_ROMAN_24, 100, 250, "skitz mate nice one! Press R to play again");
				}	
		}
	else	
		{
			if(((lander->gety() - lander->heightLeftAboveGround(ground)) < 16) && lander->gety() - lander->heightRightAboveGround(ground) < 16)	//if at ground level
				{
					lander->stop();
					drawString(GLUT_BITMAP_TIMES_ROMAN_24, 100, 220, "failure! Press R and try not suck this time");
				}
		}
}



