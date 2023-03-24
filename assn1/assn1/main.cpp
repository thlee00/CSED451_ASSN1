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

#define SCORE_MAX 999999	// Maximum score

using namespace std;

void display();
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);	// Get mouse input
void timer(int value);	// Recursive action per 1ms

bool up = false;	// Is user going up? (when jumping)
bool down = false;	// Is user going down? (after jumping)
bool eat = false;	// Is user contact with coin?
int score = 0;		// Score value
char scorebox[6] = {0 + '0',0 + '0', 0 + '0', 0 + '0', 0 + '0', 0 + '0'};	// Score box message
double position = 0;	// Camera & Score box position

Map* map;

void init(int argc, char **argv) {	// Window initialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("JuDanTae");	// Our team name

	glClearColor(0.3137, 0.7373, 1.0, 0.0);	// Skyblue RGB code
	glShadeModel(GL_FLAT);

	srand(time(NULL));
	map = new Map();
	map->init();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	map->drawUser();			// Draw user character
	map->drawTerrainBlocks();	// Draw terrain
	map->drawFireBalls();		// Draw fire balls
	map->drawCoins();			// Draw Coins

	// Draw score board
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.87 + position, 0.85);
	glVertex2f(0.87 + position, 0.95);
	glVertex2f(0.97 + position, 0.95);
	glVertex2f(0.97 + position, 0.85);
	glEnd();

	// Print real-time score
	for (int i = 1; i <= 6; i++) {
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos2f(0.95 + position - 0.01 * i, 0.89);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scorebox[i - 1]);
	}

	// Terminate program when user die
	if (map->getEndCondition()) {
		exit(0);
	}

	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)1000, (GLsizei)500);	// Make view port to 'fixed size'
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0 + position, 1 + position, 0, 1);	// Move camera position to track user
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y) {	// Get mouse input to 'jump' action
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			if (!up && !down) {
				up = true;
			}
		}
	}
}

void timer(int value) {
	map->calUserPosition(&up, &down);			// Update user position (move & jump)
	position = map->getUser()->getX() - 0.1;	// Update camera & score box position

	map->setEndCondition(map->checkEndCondition());	// Check whether user die or not

	map->newTerrainBlock();	// Spawn terrain (flat or hole)
	map->newFireBall();		// Spawn fire ball
	map->newCoin();			// Spawn coin

	//If user contacts coin, increase score and delete the coin
	eat = map->EatCoin();
	if (eat && score < SCORE_MAX) {
		score += 1;
		int tmp = score;
		for (int i = 0; i < 6; i++) {
			scorebox[i] = tmp % 10 + '0';
			tmp /= 10;
		}
	}

	reshape(1000, 500); // Camera move

	glutPostRedisplay();
	glutTimerFunc(5, timer, 1);	// Repeat every 1ms
}

int main(int argc, char** argv) {
	init(argc, argv);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutTimerFunc(5, timer, 1);
	glutMainLoop();
	return 0;
}