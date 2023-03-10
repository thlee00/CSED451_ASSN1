#include <stdlib.h>
#include <GL/glut.h>
#include <GL/GL.h>
#include <deque>
#include <string>
#include <windows.h>
#include <time.h>
#include "map.h"
#include "obj.h"

using namespace std;

void display();
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void timer(int value);

bool up = false;
bool down = false;
int score = 0;
double position = 0;

Map* map;

void init(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("JuDanTae");

	glClearColor(0.3137, 0.7373, 1.0, 0.0);
	glShadeModel(GL_FLAT);

	srand(time(NULL));
	map = new Map();
	map->init();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.5882, 0.2941, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 0.18);
	glVertex2f(1.3, 0.18);
	glVertex2f(1.3, 0.0);
	glEnd();
	//Init Soil

	glColor3f(0.0, 0.502, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.0, 0.18);
	glVertex2f(0.0, 0.2);
	glVertex2f(1.3, 0.2);
	glVertex2f(1.3, 0.18);
	glEnd();
	//Init Grass

	map->drawUser();
	map->drawTerrainBlocks();
	map->drawFireBalls();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.87 + position, 0.85);
	glVertex2f(0.87 + position, 0.95);
	glVertex2f(0.97 + position, 0.95);
	glVertex2f(0.97 + position, 0.85);
	glEnd();
	//Score Board
	/*
	if (score > 999999) score = 999999;
	for (int i = 1; i <= 6; i++) {
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos2f(0.95 + position - 0.01 * i, 0.89);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score % 10 + '0');
		score /= 10;
	}
	//Score
	*/
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)1000, (GLsizei)500);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0 + position, 1 + position, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			if (!up && !down) {
				float user_y = map->getUser()->getY();
				map->getUser()->setY(user_y + 0.01);
				up = true;
			}
		}
	}
}

void timer(int value) {
	if (up == true) {
		float user_y = map->getUser()->getY();
		if (user_y > 0.2 && user_y <= 0.45) {
			map->getUser()->setY(user_y + 0.01);
		}
		else if (user_y > 0.45) {
			up = false;
			down = true;
		}
	}
	float user_y = map->getUser()->getY();
	if (down == true) {
		if (user_y > 0.2) {
			map->getUser()->setY(user_y - 0.01);
		}
		else {
			down = false;
		}
	}
	//Jump

	float user_x = map->getUser()->getX();
	map->getUser()->setX(user_x + 0.01);
	position += 0.01;

	map->calTerrainBlock();
	map->calFireBall();

	reshape(1000, 500);
	//User & Camera Move

	score++;
	//Score

	glutPostRedisplay();
	glutTimerFunc(1, timer, 1);
}

int main(int argc, char** argv) {
	init(argc, argv);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutTimerFunc(1, timer, 1);
	glutMainLoop();

	return 0;
}