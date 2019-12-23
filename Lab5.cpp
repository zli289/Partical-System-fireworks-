// window
#include "stdafx.h"

// standard
#include <assert.h>
#include <math.h>
#include <vector>
#include <iostream>
// glut
#include <GL/glut.h>

#include "vec3.h"
#include "ball.h"

// screen size
int g_screenWidth = 0;
int g_screenHeight = 0;

// Total number of balls
int number = 20;
int particle_num=0;
static Ball balls[20];
static Ball particles[400];
static bool ball_status[20];

static bool pause=false;
// time
GLfloat t = 0.05f;
//acceleration
//coefficient of collision
GLfloat e = 0.8f; 

void init()
{
	for (int i = 0; i<number; i++)
	{
		vec3 position=vec3(RandomFloat(-1.0,1.0),RandomFloat(0.0,1.0),RandomFloat(0.0,1.0));
		vec3 velocity=vec3(RandomFloat(-1,1),RandomFloat(6,8),RandomFloat(-1,1));		
		balls[i]= Ball(velocity,position);
		ball_status[i]=true;
	}
}

void particlesfalling()
{
	for(int i=0;i<particle_num;i++)
	{
		particles[i].gravity(0.01f);
		glPushMatrix();
		glMultMatrixf(particles[i].matrix);
		glutSolidSphere(particles[i].size, 20, 20);
		glPopMatrix();		
	}

}

void ballsfalling()
{
	for (int i=0;i<number;i++)
	{
		if(balls[i].velocity.y<0)
		{
			if(ball_status[i])
			{
				particle_num+=20;
				for(int j=particle_num-20;j<particle_num;j++)
					particles[j]=Ball(vec3(RandomFloat(-2,2),RandomFloat(-2,2),RandomFloat(-2,2)),
					balls[i].position, 0.02f) ;
				ball_status[i]=false;
			}
			else
				particlesfalling();
		}
		else
		{
			glPushMatrix();
			balls[i].gravity(0.05f);
			glMultMatrixf(balls[i].matrix);
			glutSolidSphere(balls[i].size, 20, 20);
			glPopMatrix();			
		}
	}
}
void timer(int value) {
	// render
	if(!pause)
		glutPostRedisplay();
	// reset timer
	glutTimerFunc(16, timer, 0);
}

void render(void) {
	// clear buffer
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// render state
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	// enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// light source attributes
	GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat LightDiffuse[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat LightSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat LightPosition[] = { 5.0f, 5.0f, 5.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

	// surface material attributes
	GLfloat material_Ka[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	GLfloat material_Kd[] = { 0.43f, 0.47f, 0.54f, 1.0f };
	GLfloat material_Ks[] = { 0.33f, 0.33f, 0.52f, 1.0f };
	GLfloat material_Ke[] = { 0.1f, 0.0f, 0.1f, 1.0f };
	GLfloat material_Se = 10;

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_Ks);
	glMaterialfv(GL_FRONT, GL_EMISSION, material_Ke);
	glMaterialf(GL_FRONT, GL_SHININESS, material_Se);

	// modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 20.0, 15.0,0.0, 0.0, 0.0,0.0, 3.0, 0.0);

	// animation	
	ballsfalling();
	// disable lighting
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	// swap back and front buffers
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) 
{
	switch(key)
	{
		case 'a':
		pause=false;
		break;
	}
}

void reshape(int w, int h) {
	// screen size
	g_screenWidth = w;
	g_screenHeight = h;
	// viewport
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 30.0);
}

int main(int argc, char** argv) {
	// create opengL window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Lab 5 fireworks");
	// user initialization
	init();
	// set callback functions
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(16, timer, 0);
	// main loop
	glutMainLoop();

	return 0;
}