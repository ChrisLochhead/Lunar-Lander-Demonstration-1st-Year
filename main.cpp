#include "MainProgram.h"
#include "GL/glut.h"

MainProgram* mainProgram;

void keysdown(unsigned char key, int x, int y)
{
	switch (key)
	{

	case 'w':				// UP
		if (mainProgram->getLander()->getfuel() > 0)
			mainProgram->getLander()->incrementVel(0, 0.05);
		else
			mainProgram->getLander()->incrementVel(0, 0);
		break;
	case 'a':				// LEFT
		if (mainProgram->getLander()->getfuel() > 0)
			mainProgram->getLander()->incrementVel(-0.05, 0);
		else
			mainProgram->getLander()->incrementVel(0, 0);
		break;
	case 'd':				// RIGHT
		if (mainProgram->getLander()->getfuel() > 0)
			mainProgram->getLander()->incrementVel(0.05, 0);
		else
			mainProgram->getLander()->incrementVel(0, 0);
		break;
	case 'r':				// Reset 
		mainProgram->getLander()->reset();
		mainProgram->gametime = 0;
		break;
	case 27:				//  EXIT
		exit(0);
		break;
	}
}

void special_keys(int key, int x, int y)	// ARROW KEYS
{
	switch (key)
	{
	case GLUT_KEY_UP:					// ARROW UP
		if (mainProgram->getLander()->getfuel() > 0)
			mainProgram->getLander()->incrementVel(0, 0.03);
		else
			mainProgram->getLander()->incrementVel(0, 0);
		break;
	case GLUT_KEY_RIGHT:				// ARROW RIGHT
		if (mainProgram->getLander()->getfuel() > 0)
			mainProgram->getLander()->incrementVel(0.02, 0);
		else
			mainProgram->getLander()->incrementVel(0, 0);
		break;
	case GLUT_KEY_LEFT:					// ARROW LEFT
		if (mainProgram->getLander()->getfuel() > 0)
			mainProgram->getLander()->incrementVel(-0.02, 0);
		else
			mainProgram->getLander()->incrementVel(0, 0);
		break;
	}
}

void timer(int value)//update display, gravity and check for collision every 20 milliseconds
{
	display();

	mainProgram->getLander()->gravity();
	mainProgram->getLander()->windowcollisions();

	glutTimerFunc(20, timer, 0);
}


void display(void)
{
	//clear the buffer
	glClear(GL_COLOR_BUFFER_BIT);
	//disable texturing from drawing text onto the screen
	glDisable(GL_TEXTURE_2D);

	mainProgram->getBackground->draw();
	mainProgram->getGround()->show();
	mainProgram->getLander->show();

	mainProgram->collisions();

	mainProgram->status();

	glutSwapBuffers();
}

void main(int argc, char **argv)
{
	mainProgram = new MainProgram();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize((int)mainProgram->windowW, (int)mainProgram->windowH);
	glutCreateWindow("Lunar Lander game");
	gluOrtho2D(0, mainProgram->windowW, 0, mainProgram->windowH);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	mainProgram->init();
	glutDisplayFunc(display);
	glutTimerFunc(20, timer, 0);
	glutIdleFunc(display);
	glutKeyboardFunc(keysdown);
	glutSpecialFunc(special_keys);
	glutMainLoop();
}