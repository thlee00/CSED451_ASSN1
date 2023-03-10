#include "obj.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/GL.h>
#include "map.h"

using namespace std;

extern Map *map;

RectObj::RectObj() {
	x = 0.0; y = 0.0; w = 0.0; h = 0.0;
}

void RectObj::set(float _x, float _y, float _w, float _h) {
	x = _x; y = _y; w = _w; h = _h;
}

void RectObj::setX(float _x) { x = _x; }
void RectObj::setY(float _y) { y = _y; }
float RectObj::getX() { return x; }
float RectObj::getY() { return y; }
float RectObj::getW() { return w; }
float RectObj::getH() { return h; }

void RectObj::draw() {
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x, y + h);
	glVertex2f(x + w, y + h);
	glVertex2f(x + w, y);
	glEnd();
}


User::User() {
	x = 0.1, y = 0.2, w = 0.1, h = 0.3;
}

void User::draw() {
	glColor3f(0.0, 0.0, 0.0);
	RectObj::draw();
}


TerrainBlock::TerrainBlock() {
	x = 0.0, y = 0.0, w = 0.3, h = 0.2;
	bool exist = true;
}
void TerrainBlock::setExist(bool e) { exist = e; }
bool TerrainBlock::getExist() { return exist; }

void TerrainBlock::draw() {
	if (exist) {
		glColor3f(0.5882, 0.2941, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(x - w, y);
		glVertex2f(x - w, 0.18);
		glVertex2f(x, 0.18);
		glVertex2f(x, y);
		glEnd();

		glColor3f(0.0, 0.502, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(x - w, 0.18);
		glVertex2f(x - w, y+h);
		glVertex2f(x, y+h);
		glVertex2f(x, 0.18);
		glEnd();
	}
}


FireBall::FireBall() {
	x = 0.0, y = 0.0, w = 0.05, h = 0.1;
	bool elev = false;
}
void FireBall::setElev(bool e) { elev = e; }
bool FireBall::getElev() { return elev; }

void FireBall::draw() {
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x, y + h);
	glVertex2f(x + w, y + h);
	glVertex2f(x + w, y);
	glEnd();
}