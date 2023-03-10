#include "obj.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/GL.h>
#include "map.h"

using namespace std;

extern Map *map;

RectObj::RectObj() {
	x = 0; y = 0; w = 0; h = 0;
}
void RectObj::set(float _x, float _y, float _w, float _h) {
	x = _x; y = _y; w = _w; h = _h;
}
void RectObj::setX(float _x) { x = _x; }
void RectObj::setY(float _y) { y = _y; }
float RectObj::getX() { return x; }
float RectObj::getY() { return y; }
void RectObj::draw() {
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x, y + h);
	glVertex2f(x + w, y + h);
	glVertex2f(x + w, y);
	glEnd();
}

User::User() { ; }
void User::draw() {
	glColor3f(0.0, 0.0, 0.0);
	RectObj::draw();
}

Block::Block() {
	bool exist = true;
}
void Block::setExist(bool e) { exist = e; }
bool Block::getExist() { return exist; }
void Block::draw() {
	if (exist) {
		glColor3f(0.5882, 0.2941, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(x - 0.3, 0.0);
		glVertex2f(x - 0.3, 0.18);
		glVertex2f(x, 0.18);
		glVertex2f(x, 0.0);
		glEnd();

		glColor3f(0.0, 0.502, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(x - 0.3, 0.18);
		glVertex2f(x - 0.3, 0.2);
		glVertex2f(x, 0.2);
		glVertex2f(x, 0.18);
		glEnd();
	}
	else {
		glColor3f(0.0, 0.502, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(x - 0.3, 0.18);
		glVertex2f(x - 0.3, 0.2);
		glVertex2f(x, 0.2);
		glVertex2f(x, 0.18);
		glEnd();
	}
}

FireBall::FireBall() {
	bool elev = false;
}
void FireBall::setElev(bool e) { elev = e; }
bool FireBall::getElev() { return elev; }
void FireBall::draw() {
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x, y + 0.1);
	glVertex2f(x + 0.05, y + 0.1);
	glVertex2f(x + 0.05, y);
	glEnd();
}