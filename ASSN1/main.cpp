#include <stdlib.h>
#include <GL/glut.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <deque>
#include <string>
#include <windows.h>
#include <time.h>
#include "map.h"
#include "obj.h"

#define SCORE_MAX 999999 //MAXIMUM Score

using namespace std;

void display();
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void timer(int value);

bool up = false;
bool down = false;
bool eat = false; //Is user contact with coin?
int score = 0; //Score INT value
char scorebox[6] = {0 + '0',0 + '0', 0 + '0', 0 + '0', 0 + '0', 0 + '0'}; //Score box character
double position = 0; //Camera & Score box position

Map* map;
bool end_condition = false;

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

	map->drawUser();
	map->drawTerrainBlocks();
	map->drawFireBalls();
	map->drawCoins(); //Draw Coins

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.87 + position, 0.85);
	glVertex2f(0.87 + position, 0.95);
	glVertex2f(0.97 + position, 0.95);
	glVertex2f(0.97 + position, 0.85);
	glEnd();
	//Score Board Move

	for (int i = 1; i <= 6; i++) {
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos2f(0.95 + position - 0.01 * i, 0.89);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scorebox[i-1]);
	}
	//Print Real-time score

	if (end_condition) {
		exit(0);
		/*
		RectObj ending;
		ending.set(0.3, 0.3, 0.4, 0.4);
		glColor3f(0.0, 0.5, 0.5);
		ending.draw();
		*/
	}

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
				//float user_y = map->getUser()->getY();
				//map->getUser()->setY(user_y + 0.01);
				up = true;
			}
		}
	}
}

void timer(int value) {
	map->calUserPosition(&up, &down);
	//User move & jump

	position = map->getUser()->getX() - 0.1;

	end_condition = map->checkEndCondition();

	map->newTerrainBlock();
	map->newFireBall();
	map->calCoin();

	eat = map->EatCoin();
	if (eat && score < SCORE_MAX) {
		score += 1;
		int tmp = score;
		for (int i = 0; i < 6; i++) {
			scorebox[i] = tmp % 10 + '0';
			tmp /= 10;
		}
	}
	//If user eats coin, increase and update score.

	reshape(1000, 500);
	//Camera Move

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