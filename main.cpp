#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<eigen3/Eigen/Dense>
#include "transform/mirroring.hpp"
#include "transform/rotation.hpp"
#include "transform/scaling.hpp"
#include "transform/shearing.hpp"

#if defined __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#define BLACK 0, 0, 0

using namespace std;
using namespace Eigen;

//make a global variable -- for tracking the anglular position of camera
double cameraAngle;			//in radian
double cameraAngleDelta;
double cameraHeight;	
double cameraRadius;
double rectAngle;	//in degree

bool canDrawGrid;
GLUquadric *quad;

void swap(int &a,int &b) {
	int t=a;
	a=b;
	b=t;
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(BLACK, 0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/

	glMatrixMode(GL_MODELVIEW); //load the correct matrix -- MODEL-VIEW matrix
	glLoadIdentity(); 			//initialize the matrix

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera is looking?
	//3. Which direction is the camera's UP direction?

	//instead of CONSTANT information, we will define a circular path.
//	gluLookAt(-30,-30,50,	0,0,0,	0,0,1);

	gluLookAt(cameraRadius*cos(cameraAngle), cameraRadius*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	//NOTE: the camera still CONSTANTLY looks at the center
	// cameraAngle is in RADIAN, since you are using inside COS and SIN
	
	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	


	//floor
	glPushMatrix();
	{	
	glColor3f(0.0f, 1.0f, 0.0f); //green
		glBegin(GL_QUADS); //Z = 0
		{
			glVertex3f(-100,-100,0);
			glVertex3f(-100,100,0);
			glVertex3f(100,100,0);
			glVertex3f(100,-100,0);
		}glEnd();
	}glPopMatrix();	//the effect of rotation is not there now.
	
	//some gridlines along the field
	int i;
	//WILL draw grid IF the "canDrawGrid" is true:
	glColor3f(0.5f, 0.5f, 0.5f);
	if(canDrawGrid == true) {
		glBegin(GL_LINES); 
        {
			for(i=-10;i<=10;i++) {
				if(i==0)
					continue;	//SKIP the MAIN axes
				
				//lines parallel to Y-axis
				glVertex3f(i*10, -100, 0);
				glVertex3f(i*10,  100, 0);

				//lines parallel to X-axis
				glVertex3f(-100, i*10, 0);
				glVertex3f( 100, i*10, 0);
			}
		} glEnd();
	}
	
	// draw the two AXES
	glColor3f(1, 1, 1);	//100% white
	glBegin(GL_LINES);{
		//Y axis
		glVertex3f(0, -110, 0);	// intentionally extended to -150 to 150, no big deal
		glVertex3f(0,  110, 0);

		//X axis
		glVertex3f(-110, 0, 0);
		glVertex3f( 110, 0, 0);
	}glEnd();

    //Objetos() serão inseridos aqui


	//glutSwapBuffers - double buffer - um pra exibir e outro pra ir criando por tras (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void init(){
	//codes for initialization
	cameraAngle = 20;	//// init the cameraAngle
	cameraAngleDelta = 0.000; //rotation
	rectAngle = 0;
	canDrawGrid = true;
	cameraHeight = 150;
	cameraRadius = 150;

	//clear the screen
	glClearColor(BLACK, 0);
	

	quad= gluNewQuadric ();
	

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);
	
	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(70,	1,	0.1,	10000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(640, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);	//Depth, Double buffer, RGBA color

	glutCreateWindow("Scenary");

	init();
	
	glEnable(GL_DEPTH_TEST);	
	glutDisplayFunc(display);	//display callback function
	glutMainLoop();				//The main loop of OpenGL

	return 0;
}